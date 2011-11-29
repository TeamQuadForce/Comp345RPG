#include "itemrepertoire.h"
#include "armor.h"
#include "weapon.h"

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
    mItemList.append(new Armor("Padded Armor", Armor::BodyArmor, 1, 1));
    mItemList.append(new Armor("Padded Bracers", Armor::Bracers, 1, 1));
    mItemList.append(new Armor("Padded Boots", Armor::Boots, 1, 1));
    mItemList.append(new Armor("Padded Belt", Armor::Belt, 0, 1));
    mItemList.append(new Armor("Buckler", Armor::Shield, 1, 1));
    mItemList.append(new Weapon("Long Sword", Weapon::Melee, 1, 1, 8, 0, 1, 1));
    mItemList.append(new Weapon("Long Bow", Weapon::Ranged, 4, 1, 8, 0, 2, 1));
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
