#include "chestbuilder.h"

ChestBuilder::ChestBuilder()
{
    mChest = 0;
}

Chest * ChestBuilder::getChest()
{
    return mChest;
}

void ChestBuilder::createNewChest()
{
    if (mChest != 0)
    {
        delete mChest;
        mChest = 0;
    }

    mChest = new Chest;
}
