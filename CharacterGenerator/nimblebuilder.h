#ifndef NIMBLEBUILDER_H
#define NIMBLEBUILDER_H

#include "characterbuilder.h"

class NimbleBuilder : public CharacterBuilder
{
public:
    NimbleBuilder();

    void setAbilityScores(QList<short> aAbilityScoreList);

private:

    short getHighestAndRemove(QList<short> &aNumberList);
};

#endif // NIMBLEBUILDER_H
