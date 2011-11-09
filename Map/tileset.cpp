//  This class hasn't been fully implemented yet. Future uses for this class
//  is that it represents all possible tiles on the map

#include "tileset.h"
TileSet::TileSet()
{


}

TileSet::TileSet(int aRowPosition, int aColumnPosition,
                 bool aIsTerrain, QString aGamePiece)
{
    mRowPosition = aRowPosition;
    mColumnPosition = aColumnPosition;
    mIsTerrain = aIsTerrain;
    mGamePiece = aGamePiece;
}

QString TileSet::getGamePiece()
{
    return mGamePiece;
}

void TileSet::setGamePiece(QString aGamePiece)
{
    mGamePiece = aGamePiece;
}

int TileSet::rowPosition()
{
    return mRowPosition;
}

int TileSet::columnPosition()
{
    return mColumnPosition;
}

void TileSet::setRowPosition(int aRowPosition)
{
    mRowPosition = aRowPosition;
}

void TileSet::setColumnPosition(int aColumnPosition)
{
    mColumnPosition = aColumnPosition;
}

void TileSet::setIsTerrain(bool aIsTerrain)
{
    mIsTerrain = aIsTerrain;
}
