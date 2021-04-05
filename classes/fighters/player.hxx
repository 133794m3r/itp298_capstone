/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/
#ifndef ITP298_CAPSTONE_PLAYER_HXX
#define ITP298_CAPSTONE_PLAYER_HXX
#include <utility>

#include "actor.hxx"
class Player: public Actor {
  private:
	//player has their current xp and gold properties atm.
	unsigned int _xp;
	unsigned int _gold;
  public:
	//initialize the Player class with the defined properties and using the parent classes' constructor for shared properties.
	explicit Player(std::string name, unsigned char level=1, unsigned int gold=0, unsigned int hp=50, unsigned int str=6, unsigned int def=3,unsigned int xp=0): Actor(std::move(name),hp,str,def,level){
		this->_gold = gold;
		this->_xp = xp;
		//TODO: Figure out XP curve and set it to the relevant value with the level provided.
	}
};


#endif //ITP298_CAPSTONE_PLAYER_HXX
