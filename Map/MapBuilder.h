#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "map.h"
class MapBuilder // Abstract Builder
{
public:
    Map* map()
    {
        return mMap;
    }
    void createNewMapProduct()
    {
        mMap = new Map;
    }
    virtual void buildMapGrid() = 0;
    virtual void buildWall() = 0;
    virtual void buildChest() = 0;
    virtual void buildMonster() = 0;
    virtual void buildExit() = 0;
    virtual void buildLevel() = 0;
    virtual void buildCharacter() = 0;


protected:
    Map* mMap;

};

#endif // MAPBUILDER_H
