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
    mWidth = aWidth;
    mHeight = aHeight;
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
    for (int row = 0; row < mHeight; row++)
    {
        mMapGrid.append(QList<TileSet>() );
        for (int column = 0; column < mWidth; column++)
        {
            mMapGrid[row].append(TileSet(row, column, true, QString("")));
        }
    }
}

void Map::saveMap(bool aIsArena)
{
    QString fileName = QFileDialog::getSaveFileName();

    QString mapDetails;
    QString mapInformation = QString("%1,%2,%3").arg(aIsArena).arg(mWidth).arg(mHeight);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    if (file.isOpen())
    {
        out << mapInformation << endl;
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

bool Map::loadMap()
{
    bool isArena = false;
    int first = 0;
    int row = 0;
    QString line;
    QString fileName = QFileDialog::getOpenFileName();

    QFile file(fileName);
    QStringList mapTileSet;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        line = in.readLine();
        mapTileSet = line.split(",");

        if (first == 0)
        {
            isArena = mapTileSet.takeFirst().toInt();
            mWidth = mapTileSet.takeFirst().toInt();
            mHeight = mapTileSet.takeFirst().toInt();
            first = 1;
        }
        else
        {
            mMapGrid.append(QList<TileSet>() );
            for (int column = 0; column < mHeight; column++)
            {
                mMapGrid[row].append(TileSet(row, column, true, mapTileSet.takeFirst()));
                if (mMapGrid[row][column].getGamePiece().compare("You") == 0)
                {
                    setCharacterTileSet(mMapGrid[row][column]);
                    setIsCharacterPlaced(true);
                }
                if (mMapGrid[row][column].getGamePiece().compare("Exit") == 0)
                {
                    setExitTileSet(mMapGrid[row][column]);
                    setIsExitPlaced(true);
                }
                if (mMapGrid[row][column].getGamePiece().compare("Monster") == 0)
                {
                    addMonsterTileSet(mMapGrid[row][column]);
                }
            }
            row++;
        }
    }
    file.flush();
    file.close();

    displayMap();

    return isArena;
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
    return mWidth;
}

int Map::mapHeight()
{
    return mHeight;
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
    mWidth = aWidth;
}

void Map::setMapHeight(int aHeight)
{
    mHeight = aHeight;
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

bool Map::moveCharacter(QString aMovement, bool &aIsChest)
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
            if(mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("") == 0 ||
                    mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("Chest") == 0 ||
                    mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("Exit") == 0)
            {
                if (mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("Chest") == 0)
                {
                    aIsChest = true;
                }
                newRowPosition = oldRowPosition - 1;
                newColPosition = oldColPosition;
            }
            else
            {
                return false;
            }
        }
        //Character wants to move down
        else if(aMovement.compare("Down") == 0 && (oldRowPosition + 1) < mHeight)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("") == 0 ||
                    mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("Chest") == 0 ||
                    mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("Exit") == 0)
            {
                if (mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("Chest") == 0)
                {
                    aIsChest = true;
                }

                newRowPosition = oldRowPosition + 1;
                newColPosition = oldColPosition;
            }
            else
            {
                return false;
            }
        }
        //Character wants to move left
        else if(aMovement.compare("Left") == 0 && (oldColPosition - 1) >= 0)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("") == 0 ||
                    mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("Chest") == 0  ||
                    mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("Exit") == 0)
            {
                if (mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("Chest") == 0)
                {
                    aIsChest = true;
                }

                newRowPosition = oldRowPosition;
                newColPosition = oldColPosition - 1;
            }
            else
            {
                return false;
            }
        }
        //Character wants to move right
        else if(aMovement.compare("Right") == 0 && (oldColPosition + 1) < mWidth)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("") == 0 ||
                    mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("Chest") == 0 ||
                    mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("Exit") == 0)
            {
                if (mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("Chest") == 0)
                {
                    aIsChest = true;
                }

                newRowPosition = oldRowPosition;
                newColPosition = oldColPosition + 1;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        mCharacterTileSet.setRowPosition(newRowPosition);
        mCharacterTileSet.setColumnPosition(newColPosition);

        mMapGrid[newRowPosition][newColPosition].setGamePiece("You");
        TileSet aLastModifiedTileSet = mMapGrid[newRowPosition][newColPosition];
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

bool Map::moveMonster(int aIndex)
{
    const int numberOfMovements = 6;

    for (int i = 0; i < numberOfMovements; ++i)
    {
        int randomMove = qrand() % 4;
        int oldRowPosition = mMonsters[aIndex].rowPosition();
        int oldColPosition = mMonsters[aIndex].columnPosition();
        int newRowPosition = -1;
        int newColPosition = -1;


        //Character wants to move up
        if(randomMove == 0 && (oldRowPosition - 1) >= 0)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition - 1][oldColPosition].getGamePiece().compare("") == 0)
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
        else if(randomMove == 1 && (oldRowPosition + 1) < mHeight)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition + 1][oldColPosition].getGamePiece().compare("") == 0)
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
        else if(randomMove == 2 && (oldColPosition - 1) >= 0)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition][oldColPosition - 1].getGamePiece().compare("") == 0)
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
        else if(randomMove == 3 && (oldColPosition + 1) < mWidth)
        {
            //if the cell to move to is empty terrain or a chest
            if(mMapGrid[oldRowPosition][oldColPosition + 1].getGamePiece().compare("") == 0)
            {
                newRowPosition = oldRowPosition;
                newColPosition = oldColPosition + 1;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        mMonsters[aIndex].setRowPosition(newRowPosition);
        mMonsters[aIndex].setColumnPosition(newColPosition);

        mMapGrid[newRowPosition][newColPosition].setGamePiece("Monster");
        TileSet aLastModifiedTileSet = mMapGrid[newRowPosition][newColPosition];
        setLastModifiedTile(aLastModifiedTileSet);
        notifyObservers();

        mMapGrid[oldRowPosition][oldColPosition].setGamePiece("");
        aLastModifiedTileSet = mMapGrid[oldRowPosition][oldColPosition];
        setLastModifiedTile(aLastModifiedTileSet);
        notifyObservers();
    }
}

//Moves the title to a new postion and notifies any observers
void Map::moveTile(TileSet aTile, int aRow, int aColumn)
{
    mMapGrid[aRow][aColumn] = aTile;
    notifyObservers();
}

//Sets the dungeon as completed and notifies any observers
void Map::setIsDungeonCompleted(bool aCleared)
{
    mIsDungeonCompleted = aCleared;
    notifyObservers();
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

int Map::level()
{
    return mLevel;
}

void Map::setLevel(int aLevel)
{
    mLevel = aLevel;
}

void Map::addMonsterTileSet(TileSet aTileSet)
{
    mMonsters.append(aTileSet);
}
