#ifndef TANKBUILDER_H
#define TANKBUILDER_H

#include "characterbuilder.h"

class TankBuilder : public CharacterBuilder
{
public:
    TankBuilder();

    void setAbilityScores(QList<short> aAbilityScoreList);

private:
    short getHighestAndRemove(QList<short> &aNumberList);
};

#endif // TANKBUILDER_H
