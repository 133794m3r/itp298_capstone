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
Item:: Item(std::string name,
            unsigned int type
            unsigned int tier,
            unsigned int value);
{
    std::string name;
    unsigned int type;
    unsigned int value;
    unsigned int tier;

    this->name = name; //assigns the given value of name
    this->type = type;  //assigns the given value of type
    this->value = value; //assigns the given value of value
    this -> tier = tier; //assigns the given value of tier.
}

Item::~Item()
{

}

//Accessors
const std::string& get_name()
{
    return this->name; //assigns a generated item its name
}
const unsigned int& get_type()
{
    return this->type; //assigns a generated item its type
}
const unsigned int& get_value()
{
    return this->value; //assigns a generated item its value
}

//functions
const std::string Item::toString() const //this function lines 51-58 tells the program to display all item information.
{
    std::stringstream ss;

    ss << " | Name: " << this->name
        << " | Type: " << this->type
        << " | Value: " << this->value
        << "\n";

    return ss.str();
}