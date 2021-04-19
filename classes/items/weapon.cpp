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
        int damage = 0,
        unsigned int value = 0,
        unsigned int tier = 0,
        unsigned int level = 1)
        :Item(name, 1, tier, value, level) //base item constructor
{
    damage = (level * 3 + level);
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