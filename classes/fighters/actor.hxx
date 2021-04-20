/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*
*/
#ifndef ITP298_CAPSTONE_ACTOR_HXX
#define ITP298_CAPSTONE_ACTOR_HXX
#include "../../includes.hxx"
#include "../items/itembase.hxx"
#include "../items/weapon.hxx"
#include "../items/armor.hxx"
#include <sstream>

class Actor {
  private:
	//nothing just for this class atm.
	static unsigned short __next_id;
  //these properties need to be accessible by child classes.
  protected:
	const unsigned short type;
	//it would be best to make this const since it'll never be modified but it's too complex for me to get up and working.
	unsigned short id;
	std::string name_;
	//the base stats are the stats at level 1 and also are utilized to calculate the changes when leveled up.
	double bonus_hp_;
	double bonus_str_;
	double bonus_def_;
	//this contains the actual hp/str/def of the actor at it's current level. The base is the "maximum".
	unsigned int base_hp_;
	unsigned int base_str_;
	unsigned int base_def_;
	//then we store the actual values. Since they may be debuffed or if they're damaged. This way we can have stats reset.
	unsigned int hp_;
	unsigned int str_;
	unsigned int def_;
	//level can never be <0 so unsigned value.
	unsigned short lvl_ = 0;

	Weapon *weapon_held;
	Armor *armor_equipped;
	//the constructors, public methods, and getters.
  public:
	explicit Actor(std::string name="Actor", unsigned short level=1, double bonus_hp = 0.0,
				double bonus_str = 0.0, double bonus_def = 0.0,unsigned int hp = 15,
				unsigned int str = 5, unsigned int def = 3,unsigned short type=0)
				:type(type),id(__next_id++){
		//set all properties.
		//we're copying once so why not just move it.
		this->name_ = std::move(name);
		this->base_hp_ = hp;
		this->base_str_ = str;
		this->base_def_ = def;
		//these are used when leveling up to give a bonus upon that levelup beyond just their level.
		this->bonus_hp_ = bonus_hp;
		this->bonus_str_ = bonus_str;
		this->bonus_def_ = bonus_def;

		this->weapon_held = nullptr;
		this->armor_equipped = nullptr;

		this->lvl_ = level;

		if(type == 0){
			this->set_level(level);
		}
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
	unsigned short get_lvl() const{
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
	unsigned int damage(unsigned int dmg){
		if(dmg < this->def_)
			return 0;

		dmg -= this->def_;
		if(this->hp_ < dmg)
			this->hp_ = 0;
		else
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
	virtual void set_level(unsigned short level){

		int dif = 0;
		//if it's the same just do nothing.
		if(level == this->lvl_)
			dif = this->lvl_ - 1;
		else if(level > this->lvl_)
			dif = level - this->lvl_;
		else
			dif = this->lvl_ - level;
		//when they modify the level change the stats to the proper values.
		this->base_hp_ += std::lround( (this->bonus_hp_+1.0)*13.0*dif);
		this->base_str_ += std::lround( (this->bonus_str_+1.0)*4.0*dif);
		this->base_def_ += std::lround( (this->bonus_def_+1.0)*3.0*dif);
		//then set the current stats from the base.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}

	//Check if the actor is still alive. If HP is 0 then it means they're dead.
	bool is_alive(){
		return this->hp_ > 0;
	}

	void equip_weapon(Weapon &weapon){
		this->weapon_held = &weapon;
		this->str_ += weapon.get_damage();
	}

	void unequip_weapon(){
		this->str_ = this->base_str_;
	}

	void unequip_armor(){
		this->def_ = this->base_def_;
	}

	void equip_armor(Armor &armor){
		this->armor_equipped = &armor;
		this->def_ += armor.get_defense();
	}

	operator std::string() const{
		std::stringstream ss;
		ss << "id: " << this->id << " " << this->name_ << " hp:" <<this->hp_ << "/" << this->base_hp_ << " str:" << this->str_ << "/" << this->base_str_ << " def:" << this->def_ << "/" << this->base_def_;
		return ss.str();
	}
	//the friend functions to print the stuff.
	friend void show_all_stats(Actor &actor);
	friend void show_cur_stats(Actor &actor);
	friend std::ostream &operator<< (std::ostream &, const Actor &);
};

unsigned short Actor::__next_id = 0;

void show_all_stats(Actor &actor){
	std::cout << "Name:'" << actor.name_ + "' hp:" << actor.base_hp_ << " str: "
			  << actor.base_str_ << " def:" << actor.base_def_ << " level:" << std::to_string(actor.lvl_) <<
			  std::endl << "base hp:" << actor.bonus_hp_ << " base str:" <<
			  actor.bonus_str_ << " base def:" << actor.bonus_def_ << std::endl;
}

void show_cur_stats(Actor &actor){
	std::cout << "name: '" << actor.name_ << "' " << "hp:" << actor.base_hp_ << std::endl;
}

std::ostream& operator<<(std::ostream &os, const Actor &a){
	os << a.name_ << " hp:" <<a.hp_ << "/" << a.base_hp_ << " str:" << a.str_ << "/" << a.base_str_ << " def:" << a.def_ << "/" << a.base_def_;
	return os;
}
#endif //ITP298_CAPSTONE_ACTOR_HXX
