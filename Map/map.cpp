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
}

Map::Map(int aWidth, int aHeight)
{    
    width = aWidth;
    height = aHeight;
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

TileSet Map::tileSet()
{
    return lastModifiedTile;
}

TileSet Map::tileSet(int aRowPosition, int aColumnPosition)
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

void Map::setTileSet(TileSet aTileSet)
{
    lastModifiedTile = aTileSet;
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


void Map::saveMap2()
{/*

    QFile file("test.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    QDataStream & operator<< (QDataStream& out, const QList<QList<TileSet> >& );

    out << mapGrid();

    file.flush();
    file.close();*/
}




void Map::loadMap2()
{/*

    QFile file("test.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
QDataStream & operator>> (QDataStream&, QList<QList<TileSet> >& mMapGrid);
    clearMapGrid();

    in >> mMapGrid;

    file.flush();
    file.close();*/
}
