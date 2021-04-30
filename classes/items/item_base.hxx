/*
 * ITP 298 Capstone Project (itembase.hxx)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Base Item class (header) for our currently Untitled RPG. This is the building block for our weapon and armor classes
*/
#ifndef ITP298_CAPSTONE_ITEM_BASE_HXX
#define ITP298_CAPSTONE_ITEM_BASE_HXX

#include <string>
#include <sstream>
#include <cmath>
//Item Tiers 0 = trash, 1 = normal, 2 = rare, 3 = epic, 4 = legendary
class Item {

//Private variables
private:

    static unsigned short next_id; //initializes the next_id variable

protected:
    unsigned short id; // initializes the id variable
    std::string name; //used to denote the name of an item.
    unsigned int type; //used to denote the type of item upon creation.
    unsigned int tier; // used to denote the tier (rarity) of an item.
    unsigned int level;  //used to determine the level of an item.
	unsigned int value; //the value of the item


    //private functions
    void generate(); //item generation function


public:
    explicit Item(std::string name,
         unsigned int type=0,
         unsigned int tier=0,
         unsigned int level=1);



    virtual ~Item(); //calls destructor

    //Accessors
    std::string get_name() const; //allows for other files to use the private name variable
    unsigned int get_type() const; //allows for other files to use the private type variable
    unsigned int get_value() const; //allows for other files to use the private value variable
    unsigned int get_tier() const; // allows for other files to access the private tier variable
    unsigned int get_level() const; //allows for other files to access the level variable
    unsigned short get_id() const; //allows for other files to access the id variable

    //public functions
     std::string toString();
};


#endif //ITP298_CAPSTONE_ITEM_BASE_HXX
