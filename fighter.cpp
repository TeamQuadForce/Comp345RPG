#include "fighter.h"

Fighter::Fighter()
{
}

Fighter::~Fighter()
{
}

//Levels up the class. Increases the class' level by one, and
//increases the attack bonus every level. A class may also gain
//additional attacks based on certain levels.
void Fighter::levelUp()
{
    ++mLevel;

    //Gain 1 attack point for your first attack every level
    mAttackModifiers[0] = mAttackModifiers[0] + 1;

    //When you achieve level 6, 11, and 16 you achieve another attack
    if (mLevel == 6 || mLevel == 11 || mLevel == 16)
    {
        mAttackModifiers << 1;
    }

    //Gain 1 attack point for your second attack every level after level 6
    if (mLevel > 6)
    {
        mAttackModifiers[1] = mAttackModifiers[1] + 1;
    }

    //Gain 1 attack point for your third attack every level after level 11
    if (mLevel > 11)
    {
        mAttackModifiers[2] = mAttackModifiers[2] + 1;
    }

    //Gain 1 attack point for your fourth attack every level after level 16
    if (mLevel > 16)
    {
        mAttackModifiers[3] = mAttackModifiers[3] + 1;
    }
}

//Called when making a new character. The character starts at level one
//and starts with initial hit points equal to the class' hit die.
void Fighter::init()
{
    mLevel = 1;
    mHitDie = 10;
    mAttackModifiers << 1;
}

//Retrieves the class' attack bonus from the given attack number.
short Fighter::attackModifier(int aAttackNumber)
{
    if (aAttackNumber <= mAttackModifiers.size() && aAttackNumber > 0)
    {
        return mAttackModifiers.at(aAttackNumber - 1);
    }

    //Shouldn't get here, as these are called internally (error)
    return -1;
}

short Fighter::rollHitDie()
{
    return DiceRoller::d10();
}
