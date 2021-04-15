/*
 * ITP 298 Capstone Project (weapon.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Weapon class for our currently Untitled RPG.This subclass inherits properties from Item in order to produce weapons
*/
#include "weapon.hxx"

Weapon::Weapon(
        int damage_min,
        int damage_max,
        std::string name,
        unsigned int type,
        unsigned int tier,
        unsigned int value,
        unsigned int level)
        : Item(name, type, tier, value, level) //base item constructor
{
    this->damage_max = damage_max; //sets max damage value
    this->damage_min = damage_min; //sets minimum damage value
}

Weapon::~Weapon() //destructor
{

}

const std::string Weapon::toString() const //returns attributes on item (weapon)
{
    std::stringstream ss;

    ss << " | Name: " << this->get_name()
        << " | Type: " << this->get_type()
        << " | Damage: " << this->damage_min << " - " << this->damage_max;
        << " | Value: " << this->get_value()
        << " | Tier: " << this->get_tier()
        << "\n";

    return ss.str();
}