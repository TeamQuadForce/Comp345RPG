#include "armor.h"

Armor::Armor()
{
}

Armor::Armor(const QString &aItemName, const ArmorType &aArmorType) :
    mArmorType(aArmorType)
{
    Item::Item(aItemName, Item::Armor);
}

Armor::ArmorType Armor::armorType()
{
    return mArmorType;
}
