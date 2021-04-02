/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/
#ifndef ITP298_CAPSTONE_ACTOR_HXX
#define ITP298_CAPSTONE_ACTOR_HXX

class Actor {
  private:
	std::string _name;
	char _lvl;
	unsigned int _hp;
	unsigned int _str;
	unsigned int _def;
  public:
	explicit Actor(std::string name="", unsigned int hp = 0, unsigned int str=0, unsigned int def=0){
		this->_name = name;
		this->_hp = hp;
		this->_str = str;
		this->_def = def;
	}
	/**
	*
	* @parm int the amount of damage to be inflicted.
	* @return int The total amount of damage delivered. 0 for none, and - value for overkill.
	*/
	int damage(unsigned int dmg){
		dmg -= this->_def;
		if(dmg < 0)
			return 0;
		if(this->_hp < dmg)
			this->_hp = 0;
			return dmg*-1;
		}
		this->_hp -= dmg;
		return dmg;
	}
	/**
	* 
	*
	* @param the target actor to damage. Uses this object's strength.
	* @return int the amount of damage carried out.
	*/
	int attack(Actor &target){
		return target->damage(this->_str);
	}

};

#endif //ITP298_CAPSTONE_ACTOR_HXX
