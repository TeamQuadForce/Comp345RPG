#include "characterclass.h"

CharacterClass::CharacterClass() :
    mLevel(1),
    mExperience(0)
{
}

CharacterClass::~CharacterClass()
{
}

short CharacterClass::level() const
{
    return mLevel;
}

int CharacterClass::experience() const
{
    return mExperience;
}

short CharacterClass::numberOfAttacks() const
{
    return mAttackModifiers.size();
}

bool CharacterClass::isMaxLevel() const
{
    return mLevel == 20;
}

short CharacterClass::hitDie() const
{
    return mHitDie;
}
