#include "randomchestbuilder.h"
#include "itemrepertoire.h"

RandomChestBuilder::RandomChestBuilder()
{
}

void RandomChestBuilder::addItems()
{
    const unsigned int cNumOfItemsInChest = qrand() % 5 + 1;

    for (int i = 0; i < cNumOfItemsInChest; ++i)
    {
        mChest->itemList().append(ItemRepertoire::getUniqueInstance()->getRandomItem());
    }
}
