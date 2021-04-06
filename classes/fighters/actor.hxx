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
	//basic properties shared between all subclasses.
	std::string _name;
	//level can never be <0 so unsigned value.
	unsigned char _lvl;

  //these properties need to be accessible by child classes.
  protected:
//the base stats are the stats at level 1 and also are utilized to calculate the changes when leveled up.
	unsigned int _bonus_hp;
	unsigned int _bonus_str;
	unsigned int _bonus_def;
	//this contains the actual hp/str/def of the actor at it's current level. The base is the "maximum".
	unsigned int _base_hp;
	unsigned int _base_str;
	unsigned int _base_def;
	//then we store the actual values. Since they may be debuffed or if they're damaged. This way we can have stats reset.
	unsigned int _hp;
	unsigned int _str;
	unsigned int _def;
  //the constructors, public methods, and getters.
  public:
	explicit Actor(std::string name="Actor", unsigned int hp = 10, unsigned int str=6, unsigned int def=2,unsigned char level=1){
		//set all properties.
		//we're copying once so why not just move it.
		this->_name = std::move(name);
		this->_lvl = level;
		//these are used when leveling up to give a bonus upon that levelup beyond just their level.
		this->_bonus_hp = hp;
		this->_bonus_str = str;
		this->_bonus_def = def;
		//if they're higher than l1 set their stats accordingly.
		if(level > 1) {
			level--;
			//temporary growth tables until I figure out better formulas.
			//TODO: Make a growth modifier instead of just calculating from the starting stats.
			this->_base_hp = std::lround((hp * 0.25) * level) + hp;
			this->_base_str = std::lround((str * 0.15) * level) + str;
			this->_base_def = std::lround((def * 0.15) * level) + def;

		}
		else{
			//set the base ones as the values given since they're level 1.
			this->_base_hp = hp;
			this->_base_str = str;
			this->_base_def = def;
		}
		//set the current values to the base after construction.
		this->_hp = this->_base_hp;
		this->_str = this->_base_str;
		this->_def = this->_base_def;
	}

	//All of the getters.
	/**
	 *
	 * @return The name of the Actor.
	 */
	std::string get_name(){
		return this->_name;
	}

	/**
	 *
	 * @return The level of the actor
	 */
	unsigned char get_lvl(){
		return this->_lvl;
	}

	/**
	 *
	 * @return The actor's base HP.
	 */
	unsigned int get_base_hp(){
		return this->_base_hp;
	}

	/**
	 *
	 * @return The actor's current hp.
	 */
	unsigned int get_hp(){
		return this->_hp;
	}

	/**
	 *
	 * @return The actor's base strength.
	 */
	unsigned int get_base_str(){
		return this->_base_str;
	}

	/**
	 *
	 * @return The actor's current strength.
	 */
	unsigned int get_str(){
		return this->_str;
	}

	/**
	 *
	 * @return The actor's base defense.
	 */
	unsigned int get_base_def(){
		return this->_base_def;
	}

	/**
	 *
	 * @return The actor's current defense.
	 */
	unsigned int get_def(){
		return this->_def;
	}

	/**
	 *
	 * @param  the amount of damage to be inflicted.
	 * @return  The total amount of damage delivered. 0 for none, and - value for overkill.
	 */
	//TODO: Change return type/value of damage to be unsigned types.
	int damage(int dmg){
		dmg -= this->_base_def;
		if(dmg < 0)
			return 0;
		if(this->_base_hp < dmg){
			this->_base_hp = 0;
			return dmg*-1;
		}
		this->_base_hp -= dmg;
		return dmg;
	}

	/**
	 *
	 * @param the target actor to damage. Uses this object's strength.
	 * @return int the amount of damage carried out.
	 */
	int attack(Actor &target){
		return target.damage(this->_base_str);
	}

	/**
	 *
	 * @param level The level to change the actor to.
	 */
	void set_level(unsigned char level){
		//if it's the same just do nothing.
		if(level == this->_lvl)
			return;
		int dif;
		if(level > this->_lvl)
			dif = level - this->_lvl;
		else
			dif = this->_lvl - level;
		//when they modify the level change the stats to the proper values.
		this->_base_hp += std::lround((this->_bonus_hp * 0.25) * dif);
		this->_base_str += std::lround((this->_bonus_str * 0.15) * dif);
		this->_base_def += std::lround((this->_bonus_def * 0.15) * dif);
		//then set the current stats from the base.
		this->_hp = this->_base_hp;
		this->_str = this->_base_str;
		this->_def = this->_base_def;
	}

	//Check if the actor is still alive. If HP is 0 then it means they're dead.
	bool is_alive(){
		return this->_base_hp > 0;
	}

	//the friend functions to print the stuff.
	friend void show_all_stats(Actor &actor);
	friend void show_cur_stats(Actor &actor);
};

void show_all_stats(Actor &actor){
	std::cout << "Name:'" << actor._name + "' hp:" << actor._base_hp << " str: "
			  << actor._base_str << " def:" << actor._base_def << " level:" << std::to_string(actor._lvl) <<
			  std::endl << "base hp:" << actor._bonus_hp << " base str:" <<
			  actor._bonus_str << " base def:" << actor._bonus_def << std::endl;
}

void show_cur_stats(Actor &actor){
	std::cout << "name: '" << actor._name << "' " << "hp:" << actor._base_hp << std::endl;
}
#endif //ITP298_CAPSTONE_ACTOR_HXX
