#include "armor.h"

Armor::Armor()
{
}

Armor::Armor(const QString &aItemName, const ArmorType &aArmorType, const short &aArmorClass) :
    mArmorClass(aArmorClass),
    mArmorType(aArmorType)
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

void Armor::addAbilityMod(PlayerCharacter::AbilityScore aScore, short aValue)
{
    mAbilitiesToChange.append(QPair<PlayerCharacter::AbilityScore, short>(aScore, aValue));
}

QList<QPair<PlayerCharacter::AbilityScore, short> > Armor::abilityMods()
{
    return mAbilitiesToChange;
}
