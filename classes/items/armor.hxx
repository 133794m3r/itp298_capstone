/*
 * ITP 298 Capstone Project (armor.hxx)
 * Programmers: Nathaniel Mullins && Macarthur Inbody
 * Group: Dangling Pointers
 * Date: 4/5/21
 * Purpose: Armor class (header) for our currently Untitled RPG. This subclass inherits properties from Item in order to produce Armor
*/
*/
#ifndef ITP298_CAPSTONE_ARMOR_HXX
#define ITP298_CAPSTONE_ARMOR_HXX
#include "itembase.hxx"

class Armor:

        public Item {
private:
    int defence; //private variable to denote defence

public:
    Armor(
            int defence,
            const std::string name,
            const unsigned int tier,
            const unsigned int value
            const unsigned int level);

    virtual ~Armor(); //destructor

    //accessors
    inline const int& get_defence() const { return this->defence; }

    //functions
    Armor*clone() const; //function to clone armor
    std::string toString() const;
};


#endif //ITP298_CAPSTONE_ARMOR_HXX
