/*
 * ITP 298 Capstone Project (weapon.hxx)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Weapon class (header) for our currently Untitled RPG. This subclass inherits properties from Item in order to produce weapons
*/
#ifndef ITP298_CAPSTONE_WEAPON_HXX
#define ITP298_CAPSTONE_WEAPON_HXX
#include "itembase.hxx"

class Weapon: public Item
{
private:
    int damage_max; //private weapon variable for max damage
    int damage_min; //private weapon variable for minimum damage

public:
    Weapon(
            int damage_min,
            int damage_max,
            std::string name,
            unsigned int type,
            unsigned int tier,
            unsigned int value,
            unsigned int level);

    virtual ~Weapon();

    //Accessors
    inline const int& get_damage_max() const { return this->damage_max;}
    inline const int& get_damage_min() const { return this->damage_min;}

    //functions
    Weapon* clone() const;
    const std::string toString() const;


};


#endif //ITP298_CAPSTONE_WEAPON_HXX