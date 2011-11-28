#ifndef CHESTBUILDER_H
#define CHESTBUILDER_H
#include "chest.h"

class ChestBuilder
{
public:
    ChestBuilder();

    Chest* getChest();
    void createNewChest();

    virtual void addItems() = 0;

protected:
    Chest* mChest;
};

#endif // CHESTBUILDER_H
