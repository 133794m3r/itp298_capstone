/*
 * ITP 298 Capstone Project (itembase.cpp)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Base Item class for our currently Untitled RPG. This is the building block for our weapon and armor classes
*/

#include <sstream>
#include "itembase.hxx"

//Private functions
void Item::generate()
{

}



//Constructors / Destructors
Item::Item()
{
    std::string name;
    unsigned type;
    unsigned value;

    this->name = ""; //assigns the initial value of name to null
    this->type = 0;  //assigns the initial value of type to 0
    this->value = 0; //assigns the initial value of value to 0
}

Item::~Item()
{

}

//Accessors
const std::string& getName()
{
    //return this->name; //assigns a generated item its name
}
const unsigned& getType()
{
    //return this->type; //assigns a generated item its type
}
const unsigned& getValue()
{
    //return this->value; //assigns a generated item its value
}

//functions
const std::string Item::toString() const //this function lines 51-58 tells the program to display all item information.
{
    std::stringstream ss;

    ss << " - Name: " << this->name
        << " | Type: " << this->type
        << " | Value: " << this->value
        << "\n";

    return ss.str();
}