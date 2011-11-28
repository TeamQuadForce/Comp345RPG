#ifndef MAPDIRECTOR_H
#define MAPDIRECTOR_H

#include "MapBuilder.h"
class MapDirector // Director
{
public:
    void setMapBuilder(MapBuilder* aMapBuilder)
    {
        mMapBuilder = aMapBuilder;
    }
    MapBuilder* map()
    {
        return mMapBuilder;
    }
    void constructMap() // Creational process to create a Map using the builder
    {
        mMapBuilder->createNewMapProduct();
        mMapBuilder->buildMapGrid();
        mMapBuilder->buildWall();
        mMapBuilder->buildChest();
        mMapBuilder->buildExit();
        mMapBuilder->buildMonster();
        mMapBuilder->buildLevel();
        mMapBuilder->buildCharacter();
    }

private:
    MapBuilder* mMapBuilder;
};

#endif // MAPDIRECTOR_H
