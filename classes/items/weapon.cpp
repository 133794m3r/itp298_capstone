/*
 * ITP 298 Capstone Project (weapon.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Weapon class for our currently Untitled RPG.This subclass inherits properties from Item in order to produce weapons
*/
#include "weapon.hxx"

Weapon::Weapon(
        std::string name,
        int damage,
        unsigned int value,
        unsigned int tier,
        unsigned int level)
        :Item(name, 1, tier, value, level) //base item constructor
{
    damage = std::lround((level * 3.00 + level)+(level*((tier-1.00)/4.00)));
    this->damage = damage; //sets max damage value
}

Weapon::~Weapon() //destructor
{

}

std::string Weapon::toString() //returns attributes on item (weapon)
{
    std::stringstream ss;
    ss << "id = "<<this->get_id()
       << " Name = "<<this->get_name()
       << " Type = "<< this->type
       << " Damage = "<<this->get_damage()
       << " Value = "<<this->get_value()
       << " Tier = "<<this->get_tier()
       << " Level = "<<this->get_level();

    return ss.str();
}