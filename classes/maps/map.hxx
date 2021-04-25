/*
* ITP-298 Capstone Project (map.hxx)
* Group: Dangling Pointers
* Authors: Macarthur Inbody && Nathaniel Mullins
* Date: 4/20/21
* Purpose: This class creates the map which connects our rooms together.
*
*/

#ifndef ITP298_CAPSTONE_MAP_HXX
#define ITP298_CAPSTONE_MAP_HXX
#include <string>

class Map {
private:
    std::string lvl;
    std::string room_one;
    std::string room_two;
    std::string room_three;

public:
    Map(std::string lvl ="One",
        std::string room_one = "Mob",
        std::string room_two = "Boss",
        std::string room_three = "Shop");

    virtual ~Map();

    std::string Map::get_lvl() const;
    std::string get_room_one() const;
    std::string get_room_two() const;
    std::string get_room_three() const;


};


#endif //ITP298_CAPSTONE_MAP_HXX
