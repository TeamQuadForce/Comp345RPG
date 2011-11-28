#include "itemrepertoire.h"

ItemRepertoire* ItemRepertoire::mItemRepertoire = 0;

ItemRepertoire::ItemRepertoire()
{
    mItemList.clear();
}

ItemRepertoire::~ItemRepertoire()
{
    qDeleteAll(mItemList);
}

ItemRepertoire* ItemRepertoire::getUniqueInstance()
{
    if (mItemRepertoire == 0)
    {
        mItemRepertoire = new ItemRepertoire;
        mItemRepertoire->fillRepertoire();
    }

    return mItemRepertoire;
}

//fills the repertoire with hard coded items of different levels
void ItemRepertoire::fillRepertoire()
{
    //Low level items, no magical stats

}

Item * ItemRepertoire::getItem(unsigned short aLevel)
{
    //make a list containing all the items that a character this level can have
    QList<Item*> items;

    foreach(Item* item, mItemList)
    {
        if (item->level() == aLevel)
        {
            items.append(item);
        }
    }

    //Return a random item from this level list
    return items[qrand() % items.size()];
}

Item * ItemRepertoire::getRandomItem()
{
    return mItemList[qrand() % mItemList.size()];
}
