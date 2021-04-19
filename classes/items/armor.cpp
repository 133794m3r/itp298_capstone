/*
 * ITP 298 Capstone Project (armor.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose:Armor class for our currently Untitled RPG. This subclass inherits properties from Item in order to produce Armor
*/
#include "armor.hxx"
#include <string>
#include <sstream>

Armor::Armor(
        std::string name,
        int defense,
        unsigned int type,
        unsigned int tier,
        unsigned int value,
        unsigned int level)
       :Item(name, tier, type, value, level) //calls base constructor
{
    defense = (level*2 + level);
    this->defense = defense; //sets the initial value of variable defence
}

Armor::~Armor() //destructor
{

}

Armor * Armor::clone() const //function to clone armor
{
    return new Armor(*this);
}

std::string Armor::toString() //returns attributes on item (armor)
{
    std::stringstream ss;
    ss << "id = "<<this->get_id()
       << " Name = "<<this->get_name()
       << " Defense = "<<this->defense
       << " Type = "<<this->get_type()
       << " Tier = "<<this->get_tier()
       << " Value = "<<this->get_value()
       << " Level = "<<this->get_level();
return ss.str();
}