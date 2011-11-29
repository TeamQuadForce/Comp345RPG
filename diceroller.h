#ifndef DICEROLLER_H
#define DICEROLLER_H

class DiceRoller
{
public:
    static short d2();
    static short d4();
    static short d6();
    static short d8();
    static short d10();
    static short d12();
    static short d20();
    static short rollDice(short typeOfDice);
private:
    DiceRoller();
};

#endif // DICEROLLER_H
