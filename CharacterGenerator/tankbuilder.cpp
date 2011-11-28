#include "tankbuilder.h"

TankBuilder::TankBuilder()
{
}

//This will set the ability scores in the following order, from highest to lowest:
//Constitution, Dexterity, Strength, Intelligence, Charisma, Wisdom
void TankBuilder::setAbilityScores(QList<short> aAbilityScoreList)
{
    short constitution = getHighestAndRemove(aAbilityScoreList);
    short dexterity = getHighestAndRemove(aAbilityScoreList);
    short strength = getHighestAndRemove(aAbilityScoreList);
    short intelligence = getHighestAndRemove(aAbilityScoreList);
    short charisma = getHighestAndRemove(aAbilityScoreList);
    short wisdom = getHighestAndRemove(aAbilityScoreList);

    mPlayer->modifyAbilityScores(strength, dexterity, constitution,
                                 intelligence, wisdom, charisma);
}

short TankBuilder::getHighestAndRemove(QList<short> &aNumberList)
{
    short highestValue = -1;

    if (!aNumberList.isEmpty())
    {
        foreach(short number, aNumberList)
        {
            if (number > highestValue)
            {
                highestValue = number;
            }
        }

        aNumberList.removeOne(highestValue);
    }

    return highestValue;
}
