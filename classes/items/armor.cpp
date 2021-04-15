/*
 * ITP 298 Capstone Project (armor.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose:Armor class for our currently Untitled RPG. This subclass inherits properties from Item in order to produce Armor
*/
#include "armor.hxx"

Armor::Armor(
        int defence,
        std::string name,
        unsigned int tier,
        unsigned int value
        unsigned int level); //armor constructor

        :Item(name, tier, value, level) //calls base item constructor
{
    this ->defence = defence; //sets the initial value of variable defence
}

Armor::~Armor() //destructor
{

}

Armor * Armor::clone() const //function to clone armor
{
    return new Armor(*this);
}

const std::string Armor::toString() const; //returns attributes on item (armor)
{
    std::stringstream ss;

    ss << "| Name: " << this->get_name()
        << " | Type: " << this->get_type()
        << " | Defence: " << this->defence
        << " | Value: " << this->get_value()
        << " | Level: " << this->level
        << " | Tier: " << this->get_tier();

       return ss.str();
}