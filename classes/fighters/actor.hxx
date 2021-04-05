/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*
*/
#ifndef ITP298_CAPSTONE_ACTOR_HXX
#define ITP298_CAPSTONE_ACTOR_HXX
#include "../../includes.hxx"


class Actor {
  private:
	std::string _name;
	char _lvl;
	//the base stats are the stats at level 1 and also are utilized to calculate the changes when leveled up.
	unsigned int _base_hp;
	unsigned int _base_str;
	unsigned int _base_def;
	//this contains the actual hp/str/def of the actor at it's current level.
	unsigned int _hp;
	unsigned int _str;
	unsigned int _def;
  public:
	explicit Actor(std::string name="Actor", unsigned int hp = 10, unsigned int str=6, unsigned int def=2,unsigned char level=1){
		//set all properties.
		//we're copying once so why not just move it.
		this->_name = std::move(name);
		this->_lvl = level;
		this->_base_hp = hp;
		this->_base_str = str;
		this->_base_def = def;
		//if they're higher than l1 set their stats acordingly.
		if(level > 1) {
			level--;
			//temporary growth tables until I figure out better formulas.
			this->_hp = std::lround((hp * 0.25) * level) + hp;
			this->_str = std::lround((str * 0.15) * level) + str;
			this->_def = std::lround((def * 0.15) * level) + def;
		}
		else{
			//set the current ones to the starter
			_hp = hp;
			_str = str;
			_def = def;
		}
	}
	//level up actor with new stats
	void level_up(){
		//basic formulas until better ones are figured out.
		this->_hp += std::lround(this->_base_hp * 0.25);
		this->_str += std::lround(this->_base_str * 0.15);
		this->_def += std::lround(this->_base_def * 0.15);
	}
	/**
	 *
	 * @return The name of the Actor.
	 */
	std::string get_name(){
		return this->_name;
	}
	/**
	* @param  the amount of damage to be inflicted.
	* @return  The total amount of damage delivered. 0 for none, and - value for overkill.
	*/
	//TODO: Change return type/value of damage to be unsigned types.
	int damage(int dmg){
		dmg -= this->_def;
		if(dmg < 0)
			return 0;
		if(this->_hp < dmg){
			this->_hp = 0;
			return dmg*-1;
		}
		this->_hp -= dmg;
		return dmg;
	}

	/**
	* @param the target actor to damage. Uses this object's strength.
	* @return int the amount of damage carried out.
	*/
	int attack(Actor &target){
		return target.damage(this->_str);
	}
	//the friend functions to print the stuff.
	friend void show_all_stats(Actor &actor);
	friend void show_cur_stats(Actor &actor);
};

void show_all_stats(Actor &actor){
	std::cout << "Name:'" << actor._name + "' hp:" << actor._hp << " str: "
	<< actor._str << " def:" << actor._def << " level:" << std::to_string(actor._lvl) <<
	std::endl << "base hp:" << actor._base_hp << " base str:" <<
	actor._base_str << " base def:" << actor._base_def << std::endl;
}
void show_cur_stats(Actor &actor){
	std::cout << "name: '" << actor._name << "' " << "hp:" << actor._hp << std::endl;
}
#endif //ITP298_CAPSTONE_ACTOR_HXX
