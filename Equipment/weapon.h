#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item
{
public:
    enum WeaponType
    {
        Melee = 0,
        Ranged
    };

    Weapon();
    Weapon(const QString &aItemName, const WeaponType &aWeaponType, const unsigned short &aRange,
           const unsigned short &aNumOfDamageDice, const unsigned short &aDamageDie,
           const short &aMagicalDamageBonus, const unsigned short &aNumOfHands, const unsigned short &aLevel);

    WeaponType weaponType();
    unsigned short range();
    unsigned short numOfDice();
    unsigned short damageDie();
    unsigned short numOfHandsToWield();
    short magicalDamageBonus();
    QString itemDescription();

private:
    WeaponType mWeaponType;

    unsigned short mRange;
    unsigned short mNumberOfDamageDice;
    unsigned short mDamageDie;
    short mMagicalDamageBonus;
    unsigned short mNumberOfHandsToWield;
};

#endif // WEAPON_H
