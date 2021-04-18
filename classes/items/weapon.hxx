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
    int damage; //private weapon variable for damage
    public:
    Weapon(std::string name ="Weapon",
            int damage = 0,
            unsigned int type=0,
            unsigned int tier=1,
            unsigned int value=0,
            unsigned int level=1);

    virtual ~Weapon();

    //Accessors
    inline const int get_damage() const { return this->damage;} //gets the damage value of a weapon


    //functions
    Weapon* clone() const; //creates a clone of a weapon
    std::string toString() const;


};


#endif //ITP298_CAPSTONE_WEAPON_HXX