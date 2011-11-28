#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H

#include <QString>
#include <QPixmap>
#include <QList>
#include "playercharacter.h"

class CharacterBuilder
{
public:
    CharacterBuilder();
    virtual ~CharacterBuilder();

    PlayerCharacter * getPlayer();

    void createNewCharacter(const QString &aName, const QString &aGender, const QString &aRace,
                            const QString &aClassName, QPixmapData *aPortrait);

    virtual void setAbilityScores(QList<short> aAbilityScoreList) = 0;

protected:
    PlayerCharacter* mPlayer;
};

#endif // CHARACTERBUILDER_H
