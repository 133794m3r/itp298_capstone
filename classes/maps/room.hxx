/*
* ITP-298 Capstone Project (room.hxx)
* Group: Dangling Pointers
* Authors: Macarthur Inbody && Nathaniel Mullins
* Date: 4/20/21
* Purpose: This is the class which will create the "rooms" of the game; for time's sake these are shop, mob, boss, and start.
*
*/

#include<string>
#ifndef ITP298_CAPSTONE_ROOM_HXX
#define ITP298_CAPSTONE_ROOM_HXX

enum room_types{EMPTY = 1, MOB, SHOP, BOSS};

class Room {
private:
    std::string description;
    std::string room_name;

public:
    Room(std::string description = "Welcome To our game. Please Select which door you wish to enter.",
            std::string room_name = "Starting Area");

    virtual ~Room();

    std::string get_description() const;
    std::string get_room_name() const;
};


#endif //ITP298_CAPSTONE_ROOM_HXX
