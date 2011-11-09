#include "item.h"

Item::Item()
{
}

Item::Item(const QString &aItemName, const ItemType &aItemType) :
    mItemName(aItemName),
    mItemType(aItemType)
{
}

QString Item::itemName()
{
    return mItemName;
}

Item::ItemType Item::itemType()
{
    return mItemType;
}

void Item::setEquipped(bool aEquip)
{
    mIsEquipped = aEquip;
}

bool Item::isEquipped()
{
    return mIsEquipped;
}
