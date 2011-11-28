#ifndef ARENA_H
#define ARENA_H

#include "MapBuilder.h"
class Arena : public MapBuilder // Concrete Builder
{
public:
    void buildMapGrid();
    void buildWall();
    void buildChest();
    void buildMonster();
    void buildExit();
    void buildLevel();
    void buildCharacter();

};

#endif // ARENA_H
