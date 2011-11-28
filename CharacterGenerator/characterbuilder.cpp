#include "characterbuilder.h"

CharacterBuilder::CharacterBuilder() :
    mPlayer(0)
{
}

CharacterBuilder::~CharacterBuilder()
{
    delete mPlayer;
}

PlayerCharacter * CharacterBuilder::getPlayer()
{
    return mPlayer;
}

void CharacterBuilder::createNewCharacter(const QString &aName, const QString &aGender, const QString &aRace,
                                          const QString &aClassName, QPixmapData *aPortrait)
{
    if (mPlayer != 0)
    {
        delete mPlayer;
        mPlayer = 0;
    }

    mPlayer = new PlayerCharacter(aName, aGender, aRace, aClassName, aPortrait);
}

