#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
    Weapon();

    enum WeaponType
    {
        LongSword = 0,
        LongBow
    };

private:
    WeaponType mWeaponType;
    unsigned short mRange;
    unsigned short mNumberOfDamageDice;
    unsigned short mDamageDice;
    unsigned short mNumberOfHandsToWield;
};

#endif // WEAPON_H
