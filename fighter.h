#ifndef FIGHTER_H
#define FIGHTER_H

#include "characterclass.h"
#include "diceroller.h"

class Fighter : public CharacterClass
{
public:
    Fighter();
    virtual ~Fighter();

    void init();
    void levelUp();
    short attackModifier(int aAttackNumber);
    short rollHitDie();

private:

};

#endif // FIGHTER_H
