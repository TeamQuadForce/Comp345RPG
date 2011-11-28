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
    mInventory = new Inventory();
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
    notifyObservers();
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
    switch (aAbilityName)
    {
    case Strength: return mStrength;
    case Dexterity: return mDexterity;
    case Constitution: return mConstitution;
    case Intelligence: return mIntelligence;
    case Wisdom: return mWisdom;
    case Charisma: return mCharisma;
    }

    //If still here, there's a problem!
    return 0;
}

//Retrieves an ability modifier based on the given enumeration. An ability
//modifier is either positive or negative and is given by the following
//formula: (ability score) / 2 - 5.
short PlayerCharacter::abilityModifier(PlayerCharacter::AbilityScore aAbilityName)
{
    short abilityScore;

    switch (aAbilityName)
    {
    case Strength: abilityScore = mStrength; break;
    case Dexterity: abilityScore = mDexterity; break;
    case Constitution: abilityScore = mConstitution; break;
    case Intelligence: abilityScore = mIntelligence; break;
    case Wisdom: abilityScore = mWisdom; break;
    case Charisma: abilityScore = mCharisma; break;
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
        mInventory->addItem(new Weapon("Long Sword", Weapon::Melee, 1, 1, 8, 0, 1));
        mInventory->addItem(new Weapon("Long Bow", Weapon::Ranged, 4, 1, 8, 0, 2));
        Armor* armor = new Armor("hello", Armor::BodyArmor, 58);
        armor->addAbilityMod(PlayerCharacter::Strength, 80);
        mInventory->addItem(new Armor("Rags", Armor::BodyArmor, 1));
        mInventory->addItem(armor);
        mInventory->addItem(new Armor("Leather Gloves", Armor::Gloves, 1));
        mInventory->addItem(new Armor("Leather Boots", Armor::Boots, 1));

        foreach(Item* item, mInventory->backpack())
        {
            qDebug() << item->isEquipped();
        }
    }
}
