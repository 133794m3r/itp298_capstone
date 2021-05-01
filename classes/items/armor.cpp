/*
 * ITP 298 Capstone Project (armor.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose:Armor class for our currently Untitled RPG. This subclass inherits properties from Item in order to produce Armor
*/
#include "armor.hxx"
#include <utility>


Armor::Armor(
        std::string name,
        unsigned int tier,
        unsigned int level)
       :Item(std::move(name), 2, tier, level) //calls base constructor
{
	this->defense = std::lround((level * 2.00 + level)+(level*((tier-1.00)/4.00)));
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
       << " Type = "<< this->type
       << " Tier = "<<this->get_tier()
       << " Value = "<<this->get_value()
       << " Level = "<<this->get_level();
return ss.str();
}