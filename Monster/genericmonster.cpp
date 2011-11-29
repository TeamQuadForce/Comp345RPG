#include <QApplication>
#include <cmath>
#include <QDebug>
#include "genericmonster.h"
#include "diceroller.h"

GenericMonster::GenericMonster()
{
}

GenericMonster::GenericMonster(const QString &aName) :
    mName(aName)
{

}

GenericMonster::~GenericMonster()
{
}

//Initializes a new player. This involves checking for racial modifiers,
//setting the initial hit points, and setting the initial armor class.
void GenericMonster::init()
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
void GenericMonster::modifyAbilityScores(short aStrength, short aDexterity,
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
short GenericMonster::abilityScore(AbilityScore aAbilityName)
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
short GenericMonster::abilityModifier(GenericMonster::AbilityScore aAbilityName)
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

short GenericMonster::meleeAttackBonus(int aAttackNumber)
{
    return abilityModifier(Strength);
}

short GenericMonster::rangedAttackBonus(int aAttackNumber)
{
    return abilityModifier(Dexterity);
}

QString GenericMonster::name()
{
    return mName;
}

short GenericMonster::hitPoints()
{
    return mHitPoints;
}

short GenericMonster::armorClass()
{
    return mBaseArmorClass + abilityModifier(Dexterity);
}

short GenericMonster::level()
{
    return mLevel;
}

void GenericMonster::addObserver(Observer *aObserver)
{
    if (!mObserverList.contains(aObserver))
    {
        mObserverList.append(aObserver);
    }
}

void GenericMonster::removeObserver(Observer *aObserver)
{
    if (mObserverList.contains(aObserver))
    {
        mObserverList.removeOne(aObserver);
    }
}

void GenericMonster::notifyObservers()
{
    foreach (Observer * obs, mObserverList)
    {
        obs->update(this);
    }
}

short GenericMonster::rollHitDie()
{
    return DiceRoller::d10();
}

void GenericMonster::modifyStats(short aBaseArmorClass, short aBaseAttack, short aLevel)
{
    mBaseArmorClass = aBaseArmorClass;
    mBaseAttack = aBaseAttack;
    mLevel = aLevel;
}

void GenericMonster::setHitPoints(short numOfDice, short typeOfDice, short modifier)
{
    short aHitPoints = 0;

    for (int i = 0; i < numOfDice; i++)
    {
        aHitPoints += DiceRoller::rollDice(typeOfDice);
    }

    aHitPoints += modifier;

    mHitPoints = aHitPoints;
}

void GenericMonster::setDamage(short numOfDice, short typeOfDice, short modifier)
{
    short aDamage = 0;

    for (int i = 0; i < numOfDice; i++)
    {
        aDamage += DiceRoller::rollDice(typeOfDice);
    }

    aDamage += modifier;

    mDamage = aDamage;

}

