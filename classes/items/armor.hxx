/*
 * ITP 298 Capstone Project (armor.hxx)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Armor class (header) for our currently Untitled RPG. This subclass inherits properties from Item in order to produce Armor
*/
#ifndef ITP298_CAPSTONE_ARMOR_HXX
#define ITP298_CAPSTONE_ARMOR_HXX
#include "item_base.hxx"

class Armor: public Item {
private:

    int defense; //private variable to denote defence

public:
    explicit Armor(
          std::string name,
		  unsigned int tier = 0,
		  unsigned int level = 1);




	~Armor() override; //destructor

    //accessors
    inline int get_defense() const { return this->defense;}

    //functions
    Armor*clone() const; //function to clone armor
    std::string toString() override;
};


#endif //ITP298_CAPSTONE_ARMOR_HXX