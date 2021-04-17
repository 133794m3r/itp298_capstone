/*
 * ITP 298 Capstone Project (armor.hxx)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Armor class (header) for our currently Untitled RPG. This subclass inherits properties from Item in order to produce Armor
*/
#ifndef ITP298_CAPSTONE_ARMOR_HXX
#define ITP298_CAPSTONE_ARMOR_HXX
#include "itembase.hxx"

class Armor: public Item {
private:

    int defense; //private variable to denote defence

public:
    Armor(
          std::string name = "Armor",
          int defense = 0,
          unsigned int tier = 2,
          unsigned int type =4,
          unsigned int value =5,
          unsigned int level =10);



    virtual ~Armor(); //destructor

    //accessors
    inline const int& get_defense() const { return this->defense;}

    //functions
    Armor*clone() const; //function to clone armor
    std::string toString() const;
};


#endif //ITP298_CAPSTONE_ARMOR_HXX