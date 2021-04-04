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
	unsigned int _gold;
  public:
	explicit Player(std::string name, char level=1, unsigned int gold=0, unsigned int hp=50, unsigned int str=6, unsigned int def=3): Actor(std::move(name),hp,str,def,level){
		this->_gold = gold;
	}
};


#endif //ITP298_CAPSTONE_PLAYER_HXX
