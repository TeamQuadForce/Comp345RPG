//---------------------------------------------------------------------
//  Abstract class which all character classes will inherit. It contains
//  all functions and attributes which pertain to every class.
//---------------------------------------------------------------------

#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H

#include <QtCore/QList>
#include "diceroller.h"

class CharacterClass
{
public:
    CharacterClass();
    virtual ~CharacterClass();

    virtual void init() = 0;

    virtual void levelUp() = 0;
    virtual short attackModifier(int aAttackNumber) = 0;
    virtual short rollHitDie() = 0;

    short level() const;
    int experience() const;
    short numberOfAttacks() const;
    bool isMaxLevel() const;
    short hitDie() const;

protected:
    short mLevel;
    int mExperience;
    short mHitDie;

    //List of attack modifiers in case there are more than one attack,
    //each having their own modifier. Index = 0 is the first attack,
    //and so on
    QList<short> mAttackModifiers;
};

#endif // CHARACTERCLASS_H
