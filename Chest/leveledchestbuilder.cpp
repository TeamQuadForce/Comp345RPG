#include "leveledchestbuilder.h"
#include "itemrepertoire.h"

LeveledChestBuilder::LeveledChestBuilder()
{
}

void LeveledChestBuilder::addItems()
{
    const unsigned int cNumOfItemsInChest = qrand() % 5 + 1;

    for (unsigned int i = 0; i < cNumOfItemsInChest; ++i)
    {
        mChest->itemList().append(ItemRepertoire::getUniqueInstance()->getItem(mChest->level()));
    }
}
