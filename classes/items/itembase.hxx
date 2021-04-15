/*
 * ITP 298 Capstone Project (itembase.hxx)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Base Item class (header) for our currently Untitled RPG. This is the building block for our weapon and armor classes
*/
#ifndef ITP298_CAPSTONE_ITEMBASE_HXX
#define ITP298_CAPSTONE_ITEMBASE_HXX

#include <string>
#include <sstream>

enum item_types {WEAPON = 0, ARMOR}; //allows the program to decide what type of item is being generated
enum item_tiers {COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY};

class Item {

//Private variables
private:
    std::string name; //used to denote the name of an item.
    unsigned int type; //used to denote the type of item upon creation.
    unsigned int value; // used to denote the value of a generated item.
    unsigned int tier; // used to denote the tier (rarity) of an item.
    unsigned int level;  //used to determine the level of an item.

    //private functions
    void generate(); //item generation function


public:
    Item(std::string name,
         unsigned int type,
         unsigned int tier,
         unsigned int value,
         unsigned int level);

    virtual ~Item(); //calls destructor

    //Accessors
     std::string get_name() const; //allows for other files to use the private name variable
     unsigned int get_type() const; //allows for other files to use the private type variable
     unsigned int get_value() const; //allows for other files to use the private value variable
     unsigned int get_tier() const; // allows for other files to access the private tier variable
     unsigned int get_level() const; //allows for other files to access the level variable

    //public functions
    std::string toString() const;
};


#endif //ITP298_CAPSTONE_ITEMBASE_HXX
