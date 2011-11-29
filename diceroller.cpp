#include <QtGlobal>
#include <cmath>

#include "diceroller.h"

DiceRoller::DiceRoller()
{
}

short DiceRoller::d2()
{
    return (short)floor(qrand() % 2) + 1;
}

short DiceRoller::d4()
{
    return (short)floor(qrand() % 4) + 1;
}

short DiceRoller::d6()
{
    return (short)floor(qrand() % 6) + 1;
}

short DiceRoller::d8()
{
    return (short)floor(qrand() % 8) + 1;
}

short DiceRoller::d10()
{
    return (short)floor(qrand() % 10) + 1;
}

short DiceRoller::d12()
{
    return (short)floor(qrand() % 12) + 1;
}

short DiceRoller::d20()
{
    return (short)floor(qrand() % 20) + 1;
}

short DiceRoller::rollDice(short typeOfDice)
{
    if (typeOfDice == 4)
        return DiceRoller::d4();
    else if (typeOfDice == 6)
        return DiceRoller::d6();
    else if (typeOfDice == 8)
        return DiceRoller::d8();
    else if (typeOfDice == 10)
        return DiceRoller::d10();
    else if (typeOfDice == 12)
        return DiceRoller::d12();
    else if (typeOfDice ==20)
        return DiceRoller::d20();
    else
        return 0;
}

