#include "item.h"

Item::Item()
{
}

Item::Item(const QString &aItemName, const ItemType &aItemType) :
    mItemName(aItemName),
    mItemType(aItemType),
    mIsEquipped(false),
    mLevel(0)
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

unsigned short Item::level()
{
    return mLevel;
}
