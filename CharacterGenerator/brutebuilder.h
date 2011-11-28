#ifndef BRUTEBUILDER_H
#define BRUTEBUILDER_H

#include "characterbuilder.h"

class BruteBuilder : public CharacterBuilder
{
public:
    BruteBuilder();

    void setAbilityScores(QList<short> aAbilityScoreList);

private:
    short getHighestAndRemove(QList<short> &aNumberList);
};

#endif // BRUTEBUILDER_H
