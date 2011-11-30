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
    mItemList.append(new Armor("Padded Helmet", Armor::Helmet, 1, 1));
    mItemList.append(new Armor("Padded Armor", Armor::BodyArmor, 1, 1));
    mItemList.append(new Armor("Padded Bracers", Armor::Bracers, 1, 1));
    mItemList.append(new Armor("Padded Boots", Armor::Boots, 1, 1));
    mItemList.append(new Armor("Buckler", Armor::Shield, 1, 1));
    mItemList.append(new Weapon("Long Sword", Weapon::Melee, 1, 1, 8, 0, 1, 1));
    mItemList.append(new Weapon("Long Bow", Weapon::Ranged, 4, 1, 8, 0, 2, 1));

    mItemList.append(new Armor("Leather Helmet", Armor::Helmet, 2, 2));
    mItemList.append(new Armor("Leather Armor", Armor::BodyArmor, 2, 2));
    mItemList.append(new Armor("Leather Bracers", Armor::Bracers, 2, 2));
    mItemList.append(new Armor("Leather Boots", Armor::Boots, 2, 2));
    mItemList.append(new Armor("Heavy Shield", Armor::Shield, 2, 2));

    mItemList.append(new Armor("Studded Leather Helmet", Armor::BodyArmor, 3, 3));
    mItemList.append(new Armor("Studded Leather Armor", Armor::BodyArmor, 3, 3));
    mItemList.append(new Armor("Studded Leather Bracers", Armor::BodyArmor, 3, 3));
    mItemList.append(new Armor("Studded Leather Boots", Armor::BodyArmor, 3, 3));

    mItemList.append(new Armor("Chain Helmet", Armor::BodyArmor, 4, 4));
    mItemList.append(new Armor("Chain Armor", Armor::BodyArmor, 4, 4));
    mItemList.append(new Armor("Chain Bracers", Armor::BodyArmor, 4, 4));
    mItemList.append(new Armor("Chain Boots", Armor::BodyArmor, 4, 4));
    mItemList.append(new Armor("Tower Shield", Armor::Shield, 4, 4));

    mItemList.append(new Armor("Breast Plate", Armor::BodyArmor, 5, 5));
    mItemList.append(new Armor("Plate Helmet", Armor::Helmet, 5, 5));
    mItemList.append(new Armor("Plate Bracers", Armor::Bracers, 5, 5));
    mItemList.append(new Armor("Plate Boots", Armor::Boots, 5, 5));

    mItemList.append(new Armor("Banded Mail", Armor::BodyArmor, 6, 6));

    mItemList.append(new Armor("Half Plate Armor", Armor::BodyArmor, 7, 7));

    mItemList.append(new Armor("Full Plate Armor", Armor::BodyArmor, 8, 8));

}

Item * ItemRepertoire::getItem(unsigned short aLevel)
{
    //make a list containing all the items that a character this level can have
    QList<Item*> items;

    foreach(Item* item, mItemList)
    {
        if (item->level() > aLevel - 3 && item->level() <= aLevel)
        {
            items.append(item);
        }
    }

    //Return a random item from this level list
    return items.at(qrand() % items.size());
}

Item * ItemRepertoire::getRandomItem()
{
    return mItemList.at(qrand() % mItemList.size());
}
