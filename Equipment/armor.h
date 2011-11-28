#ifndef ARMOR_H
#define ARMOR_H
#include "item.h"
#include <QPair>
#include "playercharacter.h"

class Armor : public Item
{
public:
    enum ArmorType
    {
        BodyArmor = 0,
        Bracers,
        Helmet,
        Boots,
        Belt,
        Shield,
        Ring
    };

    Armor();
    Armor(const QString &aItemName, const ArmorType &aArmorType, const short &aArmorClass,
          const unsigned short &aLevel);

    ArmorType armorType();
    short armorClass();
    QString itemDescription();
    void addAbilityMod(PlayerCharacter::AbilityScore aScore, short aValue);
    QList<QPair<PlayerCharacter::AbilityScore, short> > abilityMods();

protected:
    short mArmorClass;
    ArmorType mArmorType;
    QList<QPair<PlayerCharacter::AbilityScore, short> > mAbilitiesToChange;
};

#endif // ARMOR_H
