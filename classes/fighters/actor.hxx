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
	Actor(std::string name="", unsigned int hp = 0, unsigned int str=0, unsigned int def=0){
		this->_name = name;
		this->_hp = hp;
		this->_str = str;
		this->_def = def;
	}
	bool damage(int dmg){
		if(this->_hp < dmg)
			return false;
		this->_hp -= dmg;
		return true;
	}
};

#endif //ITP298_CAPSTONE_ACTOR_HXX
