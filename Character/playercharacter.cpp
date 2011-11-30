#include <QApplication>
#include <cmath>
#include <QDebug>
#include "playercharacter.h"
#include "fighter.h"
#include "diceroller.h"
#include "weapon.h"
#include "armor.h"

PlayerCharacter::PlayerCharacter()
{
}

PlayerCharacter::PlayerCharacter(const QString &aName, const QString &aGender, const QString &aRace, const QString &aClassName, QPixmapData *aPortrait) :
    mClass(0),
    mRace(aRace),
    mClassName(aClassName),
    mGender(aGender),
    mName(aName),
    mPortrait(QPixmap(aPortrait))
{
}

PlayerCharacter::~PlayerCharacter()
{
    delete mClass;
    mClass = 0;
}

//Initializes a new player. This involves checking for racial modifiers,
//setting the initial hit points, and setting the initial armor class.
void PlayerCharacter::init()
{
    mInventory = new Inventory();

    if (mClassName == "Fighter")
    {
        mClass = new Fighter();
    }

    //If not there's a problem
    if (mClass != 0)
    {
        mClass->init();
    }
    else
    {
        //Exits out of the program
        qApp->exit(1);
    }

    //Player starts with hit points equal to his/her class' hit die roll + CON modifier
    mHitPoints = mClass->hitDie() + abilityModifier(Constitution);

    mBaseArmorClass = 10; //base AC of all players, regardless of class or race
    mLevel = 1;
    setStartingItems();

    //Notify observers that a new character is finished initializing, aka all stats are done
    notifyObservers();
}

//Increases the player's level (the class's level) by one, and performs
//any logic for leveling up. This includes increasing the maximum hit
//points of the player based on the class's hit die.
void PlayerCharacter::levelUp()
{
    //If your class is not at its maximum level (20) you may level up
    if (!mClass->isMaxLevel())
    {
        ++mLevel;
        mClass->levelUp();

        short extraHitPoints = mClass->rollHitDie() + abilityModifier(Constitution);
        if (extraHitPoints < 1)
        {
            extraHitPoints = 1;
        }

        mHitPoints += extraHitPoints;

        //Notify the observers that this character leveled up
        notifyObservers();
    }
}

//Return the character class
CharacterClass* PlayerCharacter::characterClass()
{
    return mClass;
}

Inventory* PlayerCharacter::inventory()
{
    return mInventory;
}

//Called when generating a new character. Sets all the ability scores
//to the given parameters.
void PlayerCharacter::modifyAbilityScores(short aStrength, short aDexterity,
                                          short aConstitution, short aIntelligence,
                                          short aWisdom, short aCharisma)
{
    mStrength = aStrength;
    mDexterity = aDexterity;
    mConstitution = aConstitution;
    mIntelligence = aIntelligence;
    mWisdom = aWisdom;
    mCharisma = aCharisma;
}

//Retrieves an ability score based on the given enumeration.
short PlayerCharacter::abilityScore(AbilityScore aAbilityName)
{
    //Get the equip ability scores and add it to here
    short strength = 0;
    short dexterity = 0;
    short constitution = 0;
    short intelligence = 0;
    short wisdom = 0;
    short charisma = 0;

    if (mInventory != 0)
    {
        foreach(Item* item, mInventory->backpack())
        {
            if (item->itemType() == Item::Armor && item->isEquipped())
            {
                Armor* armor = (Armor*) item;
                for (int i = 0; i < armor->abilityMods().size(); ++i)
                {
                    QPair<AbilityScore, short> pair = armor->abilityMods().at(i);
                    switch (pair.first)
                    {
                    case Strength: strength += pair.second; break;
                    case Dexterity: dexterity += pair.second; break;
                    case Constitution: constitution += pair.second; break;
                    case Intelligence: intelligence += pair.second; break;
                    case Wisdom: wisdom += pair.second; break;
                    case Charisma: charisma += pair.second; break;
                    }
                }
            }
        }
    }

    switch (aAbilityName)
    {
    case Strength: return mStrength + strength;
    case Dexterity: return mDexterity + dexterity;
    case Constitution: return mConstitution + constitution;
    case Intelligence: return mIntelligence + intelligence;
    case Wisdom: return mWisdom + wisdom;
    case Charisma: return mCharisma + charisma;
    }

    //If still here, there's a problem!
    return 0;
}

//Retrieves an ability modifier based on the given enumeration. An ability
//modifier is either positive or negative and is given by the following
//formula: (ability score) / 2 - 5.
short PlayerCharacter::abilityModifier(PlayerCharacter::AbilityScore aAbilityName)
{
    short abilityScore = 0;

    //Get the equip ability scores and add it to here
    short strength = 0;
    short dexterity = 0;
    short constitution = 0;
    short intelligence = 0;
    short wisdom = 0;
    short charisma = 0;

    if (mInventory != 0)
    {
        foreach(Item* item, mInventory->backpack())
        {
            if (item->itemType() == Item::Armor && item->isEquipped())
            {
                Armor* armor = (Armor*) item;
                for (int i = 0; i < armor->abilityMods().size(); ++i)
                {
                    QPair<AbilityScore, short> pair = armor->abilityMods().at(i);
                    switch (pair.first)
                    {
                    case Strength: strength += pair.second; break;
                    case Dexterity: dexterity += pair.second; break;
                    case Constitution: constitution += pair.second; break;
                    case Intelligence: intelligence += pair.second; break;
                    case Wisdom: wisdom += pair.second; break;
                    case Charisma: charisma += pair.second; break;
                    }
                }
            }
        }
    }

    switch (aAbilityName)
    {
    case Strength: abilityScore = mStrength + strength; break;
    case Dexterity: abilityScore = mDexterity + dexterity; break;
    case Constitution: abilityScore = mConstitution + constitution; break;
    case Intelligence: abilityScore = mIntelligence + intelligence; break;
    case Wisdom: abilityScore = mWisdom + wisdom; break;
    case Charisma: abilityScore = mCharisma + charisma; break;
    }

    return (short)floor(abilityScore / 2) - 5;
}

short PlayerCharacter::meleeAttackBonus(int aAttackNumber)
{
    return mClass->attackModifier(aAttackNumber) + abilityModifier(Strength);
}

short PlayerCharacter::rangedAttackBonus(int aAttackNumber)
{
    return mClass->attackModifier(aAttackNumber) + abilityModifier(Dexterity);
}

QString PlayerCharacter::race()
{
    return mRace;
}

QString PlayerCharacter::className()
{
    return mClassName;
}

QString PlayerCharacter::gender()
{
    return mGender;
}

QString PlayerCharacter::name()
{
    return mName;
}

short PlayerCharacter::hitPoints()
{
    return mHitPoints;
}

short PlayerCharacter::armorClass()
{
    short equipAC = 0;

    foreach (Item* item, inventory()->backpack())
    {
        if (item->itemType() == Item::Armor && item->isEquipped())
        {
            equipAC += ((Armor*)item)->armorClass();
        }
    }

    return mBaseArmorClass + abilityModifier(Dexterity) + equipAC;
}

short PlayerCharacter::level()
{
    return mLevel;
}

void PlayerCharacter::addObserver(Observer *aObserver)
{
    if (!mObserverList.contains(aObserver))
    {
        mObserverList.append(aObserver);
    }
}

void PlayerCharacter::removeObserver(Observer *aObserver)
{
    if (mObserverList.contains(aObserver))
    {
        mObserverList.removeOne(aObserver);
    }
}

void PlayerCharacter::notifyObservers()
{
    foreach (Observer * obs, mObserverList)
    {
        obs->update(this);
    }
}

QPixmap PlayerCharacter::portrait()
{
    return mPortrait;
}

void PlayerCharacter::setStartingItems()
{
    if (mClassName == "Fighter")
    {
        mInventory->addItem(new Weapon("Long Sword", Weapon::Melee, 1, 1, 8, 0, 1, 1));
        mInventory->addItem(new Weapon("Long Bow", Weapon::Ranged, 4, 1, 8, 0, 2, 1));
        Armor* armor = new Armor("Ring of Strength +1", Armor::Ring, 0, 1);
        armor->addAbilityMod(Strength, 1);
        mInventory->addItem(armor);
    }
}

short PlayerCharacter::rollInitiative(Logger* aLogger)
{
    short roll = DiceRoller::d20() + abilityModifier(Dexterity);
    aLogger->addLogEntry(QString("%1 Initiative roll is %2").arg(mName).arg(roll));
    return roll;
}

short PlayerCharacter::attack(Logger* aLogger)
{
    short fullDamage = 0;
    aLogger->addLogEntry(QString("%1 Attacks!!!").arg(mName));

    short damageDice;
    short numOfDice;
    short modifier;

    foreach(Item* item, inventory()->backpack())
    {
        if (item->isEquipped() && item->itemType() == Item::Weapon)
        {
            Weapon* weapon = (Weapon*) item;
            damageDice = weapon->damageDie();
            numOfDice = weapon->numOfDice();
            modifier = weapon->magicalDamageBonus();
        }
    }

    for (int i = 0; i < numOfDice; i++)
    {
        short damage = DiceRoller::rollDice(damageDice);
        aLogger->addLogEntry(QString("Dice number %1 (1d%3): %4 damage").arg(i + 1).arg(damageDice).arg(damage));
        fullDamage += damage;
    }

    fullDamage += modifier;
    fullDamage += abilityModifier(Strength);

    aLogger->addLogEntry(QString("Attack modifier: %1").arg(modifier));
    aLogger->addLogEntry(QString("Damage Bonus: %1").arg(abilityModifier(Strength)));
    return fullDamage;

}

QString PlayerCharacter::type()
{
    return "Player";
}

bool PlayerCharacter::takeDamage(short aDamage)
{
    mHitPoints -= aDamage;
    notifyObservers();
    return mHitPoints <= 0;
}

short PlayerCharacter::rollHit(Logger *aLogger)
{
    short d20 = DiceRoller::d20();
    aLogger->addLogEntry(QString("Rolls to hit (1d20 + BAB + STR Mod): %1 + %2 + %3").arg(d20).arg(mClass->attackModifier(1)).arg(abilityModifier(Strength)));

    return d20 + abilityModifier(Strength) + mClass->attackModifier(0);
}
