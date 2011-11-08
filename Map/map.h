#ifndef MAP_H
#define MAP_H

#include <QList>
#include "tileset.h"
#include "observable.h"

//Forward Declaration
class TileSet;
class Observable;

class Map : public Observable
{
public:
    Map();
    ~Map();
    Map(int aWidth, int aHeight);

    void displayMap();
    void saveMap();
    void saveMap2();
    void loadMap();
    void loadMap2();
    void createMapGrid();
    void clearMapGrid();

    //  Accessors
    int mapWidth();
    int mapHeight();
    QList<QList<TileSet> > mapGrid();
    TileSet tileSet(); // last modified tile will be returned
    TileSet tileSet(int aRowPosition, int aColumnPosition);


    //  Mutators
    void setMapWidth(int aWidth);
    void setMapHeight(int aHeight);
    void setTileSet(TileSet aTileSet);
    void setTileSet(TileSet aTileSet, int aRowPosition, int aColumnPosition);

    //Observer methods
    void addObserver(Observer *aObserver);
    void removeObserver(Observer *aObserver);
    void notifyObservers();

private:
    QList<QList<TileSet> > mMapGrid;
    QList<Observer*> observerList;
    int width;
    int height;
    TileSet lastModifiedTile;


//    TODO
//    bool isCharacterPlaced;
//    bool isExitPlaced;

};

#endif // MAP_H
