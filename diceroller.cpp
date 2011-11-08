#include <QtGlobal>
#include <cmath>

#include "diceroller.h"

DiceRoller::DiceRoller()
{
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
