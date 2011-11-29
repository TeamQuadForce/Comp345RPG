#include "chest.h"

Chest::Chest()
{

}

Chest::Chest(int aLevel)
{
    mLevel = aLevel;
}

QList<Item *>& Chest::itemList()
{
    return mItemList;
}

int Chest::level()
{
    return mLevel;
}
