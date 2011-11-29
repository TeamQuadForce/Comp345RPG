#include "inventory.h"
#include "armor.h"
#include "weapon.h"

Inventory::Inventory()
{
    mBackpack.clear();
}

void Inventory::addItem(Item *aItem)
{
    bool okToAdd = true;

    //if this item already exists in the backpack, dont put it in
    foreach(Item *item, mBackpack)
    {
        if (item->itemDescription() == aItem->itemDescription())
        {
            okToAdd = false;
        }
    }

    if (okToAdd)
    {
        mBackpack.append(aItem);
    }
}

void Inventory::removeItem(const int &aIndex)
{
    mBackpack.removeAt(aIndex);
}

void Inventory::equipItem(const int &aIndex)
{
    //Make sure to unequip the old item if equiping an item of the same type
    Item::ItemType type = mBackpack[aIndex]->itemType();
    if (type == Item::Armor)
    {
        //go through the list to see if it is the same type, if so unequip the original
        Armor::ArmorType subType = ((Armor*)mBackpack[aIndex])->armorType();
        foreach(Item* item, mBackpack)
        {
            if (item->itemType() == Item::Armor)
            {
                Armor* armor = (Armor*) item;
                if (subType == armor->armorType())
                {
                    if (armor->isEquipped())
                    {
                        armor->setEquipped(false);
                    }
                }
            }
        }
    }
    else if (type == Item::Weapon)
    {
        Weapon::WeaponType subType = ((Weapon*)mBackpack[aIndex])->weaponType();
        foreach(Item* item, mBackpack)
        {
            if (item->itemType() == Item::Weapon)
            {
                Weapon* weapon = (Weapon*) item;
                if (subType == weapon->weaponType())
                {
                    if (weapon->isEquipped())
                    {
                        weapon->setEquipped(false);
                    }
                }
            }
        }
    }

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
