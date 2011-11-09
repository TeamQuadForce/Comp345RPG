#include "armor.h"

Armor::Armor()
{
}

Armor::Armor(const QString &aItemName, const ArmorType &aArmorType, const short &aArmorClass) :
    mArmorType(aArmorType),
    mArmorClass(aArmorClass)
{
    mItemName = aItemName;
    mItemType = Item::Armor;
}

Armor::ArmorType Armor::armorType()
{
    return mArmorType;
}

short Armor::armorClass()
{
    return mArmorClass;
}

QString Armor::itemDescription()
{
    return QString("%1 (+%2 AC)").arg(mItemName).arg(mArmorClass);
}
