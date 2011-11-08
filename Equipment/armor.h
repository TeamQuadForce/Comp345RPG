#ifndef ARMOR_H
#define ARMOR_H

class Armor
{
public:
    enum ArmorType
    {
        BodyArmor = 0,
        Hand,
        Ring,
        Helmet,
        Boot,
        Belt
    };

    Armor(const ArmorType &aArmorType);



private:

};

#endif // ARMOR_H
