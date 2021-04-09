/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/
#ifndef ITP298_CAPSTONE_MOB_HXX
#define ITP298_CAPSTONE_MOB_HXX

#include "actor.hxx"

class Mob : public Actor {
private:
	//the xp to be awarded and gold be awarded upon death.
	unsigned int _xp;
	unsigned int _gold;
public:
	//initialize the Mob class. Explicit since it can be called with just 1 parameter. Also initialize properites with parent class' constructor.
	explicit Mob(std::string name="Mob", uint32_t xp=0, uint32_t gold=0, unsigned int hp = 12, unsigned int def = 4):Actor(std::move(name),hp,5,def) {
		this->_xp = xp;
		this->_gold = gold;
	}
	/**
	 * Returns the rewards upon death.
	 *
	 * @return a std::pair struct with all of the data set.
	 */
	std::pair<unsigned int, unsigned int> rewards() {
		return std::make_pair(this->_xp, this->_gold);
	}
};


#endif //ITP298_CAPSTONE_MOB_HXX
