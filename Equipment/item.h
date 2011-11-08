#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    enum ItemType
    {
        UsableItem = 0,
        Weapon,
        Armor,
        Ring
    };

    Item();
    Item(const QString &aItemName, const ItemType &aItemType);

    QString itemName();
    ItemType itemType();

private:
    QString mItemName;
    ItemType mItemType;
};

#endif // ITEM_H
