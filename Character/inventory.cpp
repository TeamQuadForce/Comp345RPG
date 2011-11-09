#include "inventory.h"

Inventory::Inventory()
{
}

void Inventory::addItem(Item *aItem)
{
    mBackpack.append(aItem);
}

void Inventory::removeItem(const int &aIndex)
{
    mBackpack.removeAt(aIndex);
}

void Inventory::equipItem(const int &aIndex)
{
    mBackpack[aIndex]->setEquipped(true);
}

void Inventory::unequipItem(const int &aIndex)
{
    mBackpack[aIndex]->setEquipped(false);
}

QList<Item*> Inventory::backpack()
{
    return mBackpack;
}
