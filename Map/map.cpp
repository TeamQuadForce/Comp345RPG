#include "map.h"
#include <QIntValidator>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDataStream>
#include <QFileDialog>
#include <QObject>

//  Constructors
Map::Map()
{
    mIsCharacterPlaced = false;
    mIsExitPlaced = false;
    mIsDungeonCompleted = false;
}

Map::Map(int aWidth, int aHeight)
{    
    width = aWidth;
    height = aHeight;
    mIsCharacterPlaced = false;
    mIsExitPlaced = false;
    mIsDungeonCompleted = false;
}

//  Destructor
Map::~Map()
{
}

void Map::clearMapGrid()
{
    for (int row=0; row<mMapGrid.size() ; row++)
    {
        mMapGrid[row].clear();
    }
    mMapGrid.clear();
}

void Map::displayMap()
{
    QTextStream cout(stdout, QIODevice::WriteOnly);

    for (int row=0; row<mMapGrid.size() ; row++)
    {
        for (int column=0; column<mMapGrid[row].size(); column++)
        {
            cout << mMapGrid[row][column].getGamePiece();
        }
        cout << endl;
    }
}

void Map::createMapGrid()
{
    for (int row = 0; row < height; row++)
    {
        mMapGrid.append(QList<TileSet>() );
        for (int column = 0; column < width; column++)
        {
            mMapGrid[row].append(TileSet(row, column, true, QString("")));
        }
    }
}

void Map::saveMap()
{
    QString fileName = QFileDialog::getSaveFileName();

    QString mapDetails;
    QString mapDimensions = QString("%1,%2").arg(width).arg(height);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    if (file.isOpen())
    {
        out << mapDimensions << endl;
        for (int row = 0; row < mMapGrid.size(); row++)
        {
            for (int column = 0; column < mMapGrid[row].size(); column++)
            {
                mapDetails += mMapGrid[row][column].getGamePiece() + ",";

            }
            mapDetails.truncate(mapDetails.size()-1);
            out << mapDetails << endl;
            mapDetails = "";
        }
        file.flush();
        file.close();
    }

}

void Map::loadMap()
{
    int first = 0;
    int row = 0;
    QString line;
    QString fileName = QFileDialog::getOpenFileName();

    QFile file(fileName);
    QStringList mapTileSet;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        line = in.readLine();
        mapTileSet = line.split(",");

        if (first == 0)
        {
            width = mapTileSet.takeFirst().toInt();
            height = mapTileSet.takeFirst().toInt();
            first = 1;
        }
        else
        {
            mMapGrid.append(QList<TileSet>() );
            for (int column = 0; column < height; column++)
            {
                mMapGrid[row].append(TileSet(row, column, true, mapTileSet.takeFirst()));
                if (mMapGrid[row][column].getGamePiece().compare("Character") == 0)
                {
                    setCharacterTileSet(mMapGrid[row][column]);
                    setIsCharacterPlaced(true);
                }
                if (mMapGrid[row][column].getGamePiece().compare("Exit") == 0)
                {
                    setExitTileSet(mMapGrid[row][column]);
                    setIsExitPlaced(true);
                }
            }
            row++;
        }
    }
    file.flush();
    file.close();

    displayMap();
}

//  Accessors

QList<QList<TileSet> > Map::mapGrid()
{
    return mMapGrid;
}

TileSet Map::lastModifiedTileSet()
{
    return mLastModifiedTile;
}

TileSet Map::mapGridTileSet(int aRowPosition, int aColumnPosition)
{
    return mMapGrid[aRowPosition][aColumnPosition];
}

int Map::mapWidth()
{
    return width;
}

int Map::mapHeight()
{
    return height;
}


//  Mutators

void Map::setLastModifiedTile(TileSet aTileSet)
{
    mLastModifiedTile = aTileSet;
}

void Map::setTileSet(TileSet aTileSet, int aRowPosition, int aColumnPosition)
{
    mMapGrid[aRowPosition][aColumnPosition] = aTileSet;
}

void Map::setMapWidth(int aWidth)
{
    width = aWidth;
}

void Map::setMapHeight(int aHeight)
{
    height = aHeight;
}



//  Observer methods
void Map::addObserver(Observer *aObserver)
{
    if (!observerList.contains(aObserver))
    {
        observerList.append(aObserver);
    }
}

void Map::removeObserver(Observer *aObserver)
{
    if (observerList.contains(aObserver))
    {
        observerList.removeOne(aObserver);
    }
}

void Map::notifyObservers()
{
    foreach (Observer * obs, observerList)
    {
        obs->update(this);
    }
}

bool Map::moveCharacter(QString aMovement)
{
    int oldRowPosition = mCharacterTileSet.rowPosition();
    int oldColPosition = mCharacterTileSet.columnPosition();
    int newRowPosition = -1;
    int newColPosition = -1;

    //If the character isn't place or the movement ID is invalid
    if (!mIsCharacterPlaced)
    {
        return false;
    }
    else
    {
        //Character wants to move up
        if(aMovement.compare("Up") == 0 && (oldRowPosition - 1) >= 0)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("Terrain") == 0 ||
                    mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("Chest") == 0 ||
                    mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("Exit") == 0)
            {
                newRowPosition = oldRowPosition - 1;
                newColPosition = oldColPosition;
            }
            else
            {
                return false;
            }
        }

        //Character wants to move down
        if(aMovement.compare("Down") == 0 && (oldRowPosition + 1) < height)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("Terrain") == 0 ||
                    mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("Chest") ||
                    mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("Exit") == 0)
            {
                newRowPosition = oldRowPosition + 1;
                newColPosition = oldColPosition;
            }
            else
            {
                return false;
            }
        }

        //Character wants to move left
        if(aMovement.compare("Left") == 0 && (oldColPosition - 1) >= 0)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("Terrain") == 0 ||
                    mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("Chest") == 0  ||
                    mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("Exit") == 0)
            {
                newRowPosition = oldRowPosition;
                newColPosition = oldColPosition - 1;
            }
            else
            {
                return false;
            }
        }

        //Character wants to move right
        if(aMovement.compare("Right") == 0 && (oldColPosition + 1) < width)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("Terrain") == 0 ||
                    mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("Chest") == 0 ||
                    mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("Exit") == 0)
            {
                newRowPosition = oldRowPosition;
                newColPosition = oldColPosition + 1;
            }
            else
            {
                return false;
            }
        }

        mCharacterTileSet.setRowPosition(newRowPosition);
        mCharacterTileSet.setColumnPosition(newColPosition);
        TileSet aLastModifiedTileSet = mMapGrid[newRowPosition][newColPosition];

        mMapGrid[newRowPosition][newColPosition].setGamePiece("Character");
        setLastModifiedTile(aLastModifiedTileSet);
        notifyObservers();

        mMapGrid[oldRowPosition][oldColPosition].setGamePiece("");
        aLastModifiedTileSet = mMapGrid[oldRowPosition][oldColPosition];
        setLastModifiedTile(aLastModifiedTileSet);
        notifyObservers();

        if(mCharacterTileSet.rowPosition() == mExitTileSet.rowPosition() &&
                mCharacterTileSet.columnPosition() == mExitTileSet.columnPosition())
        {
            setIsDungeonCompleted(true);
        }
        return true;
    }
}

//Moves the title to a new postion and notifies any observers
void Map::moveTile(TileSet tile, int row, int column)
{
    mMapGrid[row][column] = tile;
    notifyObservers();
}

//Sets the dungeon as completed and notifies any observers
void Map::setIsDungeonCompleted(bool cleared)
{
    mIsDungeonCompleted = cleared;
//    notifyObservers();
}

//Return  if the dungeon is completed
bool Map::isDungeonCompleted()
{
    return mIsDungeonCompleted;
}

bool Map::isCharacterPlaced()
{
    return mIsCharacterPlaced;
}

bool Map::isExitPlaced()
{
    return mIsExitPlaced;
}

void Map::setCharacterTileSet(TileSet aTileSet)
{
    mCharacterTileSet = aTileSet;
}

void Map::setExitTileSet(TileSet aTileSet)
{
    mExitTileSet = aTileSet;
}

TileSet Map::characterTileSet()
{
    return mCharacterTileSet;
}

TileSet Map::exitTileSet()
{
    return mExitTileSet;
}

void Map::setIsCharacterPlaced(bool aIsCharacterPlaced)
{
    mIsCharacterPlaced = aIsCharacterPlaced;
}

void Map::setIsExitPlaced(bool aIsExitPlaced)
{
    mIsExitPlaced = aIsExitPlaced;
}
