#include <QApplication>
#include <cmath>
#include <QDebug>
#include "monster.h"
#include "diceroller.h"
#include <QStringList>

Monster::Monster()
{
}

Monster::Monster(const QString &aName) :
    mName(aName)
{

}

Monster::~Monster()
{
}

//Initializes a new player. This involves checking for racial modifiers,
//setting the initial hit points, and setting the initial armor class.
void Monster::init()
{

    //Player starts with hit points equal to his/her class' hit die roll + CON modifier
    mHitPoints = abilityModifier(Constitution);

    mBaseArmorClass = 10; //base AC of all players, regardless of class or race
    mLevel = 1;

    //Notify observers that a new character is finished initializing, aka all stats are done
    notifyObservers();
}

//Called when generating a new character. Sets all the ability scores
//to the given parameters.
void Monster::modifyAbilityScores(short aStrength, short aDexterity,
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
short Monster::abilityScore(AbilityScore aAbilityName)
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
short Monster::abilityModifier(Monster::AbilityScore aAbilityName)
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

short Monster::meleeAttackBonus(int aAttackNumber)
{
    return abilityModifier(Strength);
}

short Monster::rangedAttackBonus(int aAttackNumber)
{
    return abilityModifier(Dexterity);
}

QString Monster::name()
{
    return mName;
}

short Monster::hitPoints()
{
    return mHitPoints;
}

short Monster::armorClass()
{
    return mBaseArmorClass + abilityModifier(Dexterity);
}

short Monster::level()
{
    return mLevel;
}

void Monster::addObserver(Observer *aObserver)
{
    if (!mObserverList.contains(aObserver))
    {
        mObserverList.append(aObserver);
    }
}

void Monster::removeObserver(Observer *aObserver)
{
    if (mObserverList.contains(aObserver))
    {
        mObserverList.removeOne(aObserver);
    }
}

void Monster::notifyObservers()
{
    foreach (Observer * obs, mObserverList)
    {
        obs->update(this);
    }
}

short Monster::rollHitDie()
{
    return DiceRoller::d10();
}

void Monster::modifyStats(short aBaseArmorClass, short aBaseAttack, short aLevel)
{
    mBaseArmorClass = aBaseArmorClass;
    mBaseAttack = aBaseAttack;
    mLevel = aLevel;
}

void Monster::setHitPoints(short numOfDice, short typeOfDice, short modifier)
{
    short aHitPoints = 0;

    for (int i = 0; i < numOfDice; i++)
    {
        aHitPoints += DiceRoller::rollDice(typeOfDice);
    }

    aHitPoints += modifier;

    mHitPoints = aHitPoints;
}

short Monster::attack(Logger* aLogger)
{
    short fullDamage = 0;

    aLogger->addLogEntry(QString("%1 attacks!!: ").arg(mName));
    for (int i = 0; i < mAttackRolls; i++)
    {
        short damage = DiceRoller::rollDice(mAttackDice);
        aLogger->addLogEntry(QString("Dice number %1 (1d%3): %4 damage").arg(i + 1).arg(mAttackDice).arg(damage));
        fullDamage += damage;
    }

    fullDamage += mAttackModifier;
    if (fullDamage < 0)
    {
        fullDamage = 0;
    }

    aLogger->addLogEntry(QString("Attack modifier: %1").arg(mAttackModifier));

    return fullDamage;
}

void Monster::modifyAttack(short aAttackRolls, short aAttackDice, short aAttackModifier)
{
    mAttackRolls = aAttackRolls;
    mAttackDice = aAttackDice;
    mAttackModifier = aAttackModifier;
}

short Monster::rollInitiative(Logger* aLogger)
{
    short roll = DiceRoller::d20() + abilityModifier(Dexterity);
    aLogger->addLogEntry(QString("%1 Initiative roll is %2").arg(mName).arg(roll));
    return roll;
}

QString Monster::type()
{
    return "Monster";
}

bool Monster::takeDamage(short aDamage)
{
    mHitPoints -= aDamage;
    return mHitPoints <= 0;
}

short Monster::rollHit(Logger *aLogger)
{
    short d20 = DiceRoller::d20();
    aLogger->addLogEntry(QString("Rolls to hit (1d20 + BAB + STR Mod): %1 + %2 + %3").arg(d20).arg(mBaseAttack).arg(abilityModifier(Strength)));

    return d20 + abilityModifier(Strength) + mBaseAttack;
}

