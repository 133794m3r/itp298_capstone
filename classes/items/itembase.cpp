/*
 * ITP 298 Capstone Project (itembase.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Base Item class for our currently Untitled RPG. This is the building block for our weapon and armor classes
*/


#include "itembase.hxx"

//Private functions
void Item::generate()
{

}



//Constructors / Destructors
Item::Item(std::string name,
unsigned int type,
unsigned int tier,
unsigned int value,
unsigned int level){

this->name = name; //assigns the given value of name
this->type = type;  //assigns the given value of type
this->value = value; //assigns the given value of value
this->tier = tier; //assigns the given value of tier
this->level = level;} //assigns the given value of level


Item::~Item()
{

}

//Accessors
std::string get_name()
{
     return this->name; //assigns a generated item its name
}
unsigned int get_type()
{
     return this->type; //assigns a generated item its type
}
unsigned int get_value()
{
    return this->value; //assigns a generated item its value
}
unsigned int get_level()
{
     return this->level; //assigns level to generated items
}
unsigned int get_tier()
{
    return this->tier; //assigns tier(rarity) to generated items
}

//functions
std::string Item::toString() const //this function lines 51-58 tells the program to display all item information.
{
    std::stringstream ss;

    ss << " | Name: " << this->name
        << " | Type: " << this->type
        << " | Value: " << this->value
        << " | Level: " << this->level
        << " | Tier: " << this->tier
        << "\n";

    return ss.str();
}