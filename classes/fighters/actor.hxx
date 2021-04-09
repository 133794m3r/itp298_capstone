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
	std::string name_;

	//level can never be <0 so unsigned value.
	unsigned char lvl_;

  //these properties need to be accessible by child classes.
  protected:
//the base stats are the stats at level 1 and also are utilized to calculate the changes when leveled up.
	unsigned int bonus_hp_;
	unsigned int bonus_str_;
	unsigned int bonus_def_;
	//this contains the actual hp/str/def of the actor at it's current level. The base is the "maximum".
	unsigned int base_hp_;
	unsigned int base_str_;
	unsigned int base_def_;
	//then we store the actual values. Since they may be debuffed or if they're damaged. This way we can have stats reset.
	unsigned int hp_;
	unsigned int str_;
	unsigned int def_;
  //the constructors, public methods, and getters.
  public:
	explicit Actor(std::string name="Actor", unsigned int hp = 10, unsigned int str=6, unsigned int def=2,unsigned char level=1){
		//set all properties.
		//we're copying once so why not just move it.
		this->name_ = std::move(name);
		this->lvl_ = level;
		//these are used when leveling up to give a bonus upon that levelup beyond just their level.
		this->bonus_hp_ = hp;
		this->bonus_str_ = str;
		this->bonus_def_ = def;
		//if they're higher than l1 set their stats accordingly.
		if(level > 1) {
			level--;
			//temporary growth tables until I figure out better formulas.
			//TODO: Make a growth modifier instead of just calculating from the starting stats.
			this->base_hp_ = std::lround((hp * 0.25) * level) + hp;
			this->base_str_ = std::lround((str * 0.15) * level) + str;
			this->base_def_ = std::lround((def * 0.15) * level) + def;

		}
		else{
			//set the base ones as the values given since they're level 1.
			this->base_hp_ = hp;
			this->base_str_ = str;
			this->base_def_ = def;
		}
		//set the current values to the base after construction.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}

	//All of the getters.
	/**
	 *
	 * @return The name of the Actor.
	 */
	std::string get_name() const{
		return this->name_;
	}

	/**
	 *
	 * @return The level of the actor
	 */
	unsigned char get_lvl() const{
		return this->lvl_;
	}

	/**
	 *
	 * @return The actor's base HP.
	 */
	unsigned int get_base_hp() const{
		return this->base_hp_;
	}

	/**
	 *
	 * @return The actor's current hp.
	 */
	unsigned int get_hp() const{
		return this->hp_;
	}

	/**
	 *
	 * @return The actor's base strength.
	 */
	unsigned int get_base_str() const{
		return this->base_str_;
	}

	/**
	 *
	 * @return The actor's current strength.
	 */
	unsigned int get_str() const{
		return this->str_;
	}

	/**
	 *
	 * @return The actor's base defense.
	 */
	unsigned int get_base_def() const{
		return this->base_def_;
	}

	/**
	 *
	 * @return The actor's current defense.
	 */
	unsigned int get_def() const{
		return this->def_;
	}

	/**
	 *
	 * @param  the amount of damage to be inflicted.
	 * @return  The total amount of damage delivered. 0 for none, and - value for overkill.
	 */
	//TODO: Change return type/value of damage to be unsigned types.
	int damage(int dmg){
		dmg -= this->def_;
		if(dmg < 0)
			return 0;
		if(this->hp_ < dmg){
			this->hp_ = 0;
			return dmg*-1;
		}
		this->hp_ -= dmg;
		return dmg;
	}

	/**
	 *
	 * @param the target actor to damage. Uses this object's strength.
	 * @return int the amount of damage carried out.
	 */
	int attack(Actor &target){
		return target.damage(this->base_str_);
	}

	/**
	 *
	 * @param level The level to change the actor to.
	 */
	void set_level(unsigned char level){
		//if it's the same just do nothing.
		if(level == this->lvl_)
			return;
		int dif;
		if(level > this->lvl_)
			dif = level - this->lvl_;
		else
			dif = this->lvl_ - level;
		//when they modify the level change the stats to the proper values.
		this->base_hp_ += std::lround((this->bonus_hp_ * 0.25) * dif);
		this->base_str_ += std::lround((this->bonus_str_ * 0.15) * dif);
		this->base_def_ += std::lround((this->bonus_def_ * 0.15) * dif);
		//then set the current stats from the base.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}

	//Check if the actor is still alive. If HP is 0 then it means they're dead.
	bool is_alive(){
		return this->hp_ > 0;
	}

	//the friend functions to print the stuff.
	friend void show_all_stats(Actor &actor);
	friend void show_cur_stats(Actor &actor);
};

void show_all_stats(Actor &actor){
	std::cout << "Name:'" << actor.name_ + "' hp:" << actor.base_hp_ << " str: "
			  << actor.base_str_ << " def:" << actor.base_def_ << " level:" << std::to_string(actor.lvl_) <<
			  std::endl << "base hp:" << actor.bonus_hp_ << " base str:" <<
			  actor.bonus_str_ << " base def:" << actor.bonus_def_ << std::endl;
}

void show_cur_stats(Actor &actor){
	std::cout << "name: '" << actor.name_ << "' " << "hp:" << actor.base_hp_ << std::endl;
}
#endif //ITP298_CAPSTONE_ACTOR_HXX
