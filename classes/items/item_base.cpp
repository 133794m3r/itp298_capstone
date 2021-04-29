/*
 * ITP 298 Capstone Project (itembase.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Base Item class for our currently Untitled RPG. This is the building block for our weapon and armor classes
*/


#include "item_base.hxx"

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

value = level *6 + 25 + level;
this->id = next_id++; //increments item id
this->name = std::move(name); //assigns the given value of name
this->type = type;  //assigns the given value of type
this->value = value; //assigns the given value of value
this->tier = tier; //assigns the given value of tier
this->level = level;}//assigns the given value of level

unsigned short Item::next_id = 0; //sets the variable next_id to 0


Item::~Item()
{

}

//Accessors
std::string Item::get_name() const
{
    return this->name; //assigns a generated item its name
}
unsigned int Item::get_type() const
{
    return this->type; //assigns a generated item its type
}
unsigned int Item::get_value() const
{
    return this->value; //assigns a generated item its value
}
unsigned int Item::get_level() const
{
    return this->level; //assigns level to generated items
}
unsigned int Item::get_tier() const
{
    return this->tier; //assigns tier(rarity) to generated items
}
unsigned short Item::get_id() const
{
    return this->id;
}



//functions
    std::string Item::toString() {
    std::stringstream ss;
    ss << "id = " <<this->id
       << " Name = " <<this->name
       << " Type = " <<this->type
       << " Tier = " <<this->tier
       << " Value = " <<this->value
       << " Level = " <<this->level;

    return ss.str();
}
