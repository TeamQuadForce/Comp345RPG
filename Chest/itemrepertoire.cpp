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

void ItemRepertoire::fillRepertoire()
{

}
