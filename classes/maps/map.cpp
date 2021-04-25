/*
* ITP-298 Capstone Project map.cpp)
* Group: Dangling Pointers
* Authors: Macarthur Inbody && Nathaniel Mullins
* Date: 4/20/21
* Purpose: This class creates the map which connects the rooms of our rpg together
*
*/

#include "map.hxx"

Map::Map(std::string lvl,
         std::string room_one,
         std::string room_two,
         std::string room_three) {

    lvl = this->lvl;

};

    Map::~Map()
    {

    }

    std::string Map::get_lvl() const {
        return this->lvl;
    }
    std::string Map::get_room_one() const {
        return this->room_one;
    }
    std::string Map::get_room_two() const {
        return this->room_two;
    }
    std::string Map::get_room_three() const {
        return this->room_three;
    }


