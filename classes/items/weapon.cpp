/*
 * ITP 298 Capstone Project (weapon.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Weapon class for our currently Untitled RPG.This subclass inherits properties from Item in order to produce weapons
*/
#include "weapon.hxx"

Weapon::Weapon(
        int damage,
        std::string name,
        unsigned int type,
        unsigned int tier,
        unsigned int value,
        unsigned int level)
        : Item(name, type, tier, value, level) //base item constructor
{
    damage = level * 2.95 + level;
    this->damage = damage; //sets max damage value
}

Weapon::~Weapon() //destructor
{

}

std::string Weapon::toString() const //returns attributes on item (weapon)
{
    std::stringstream ss;

    ss << " | Name: " << this->get_name()
       << " | Type: " << this->get_type()
       << " | Damage: " << this->get_damage()
       << " | Value: " << this->get_value()
       << " | Tier: " << this->get_tier()
       << "\n";

    return ss.str();
}