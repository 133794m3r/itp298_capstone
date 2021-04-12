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
	unsigned int xp_;
	unsigned int gold_;
  public:
	//initialize the Player class with the defined properties and using the parent classes' constructor for shared properties.
	explicit Player(std::string name, unsigned short level=1,double bonus_hp = 0.0, double bonus_str = 0.0, double bonus_def = 0.0): Actor(std::move(name),level,bonus_hp, bonus_str,bonus_def,20,5,4){
		this->gold_ = 0;
		this->xp_ = 0;
		//TODO: Figure out XP curve and set it to the relevant value with the level provided.
		Actor::set_level(level);
	}

	//level up actor with new stats
	void level_up(){
		unsigned int old_hp = this->base_hp_;
		unsigned int old_str = this->base_str_;
		unsigned int old_def = this->base_def_;
		//basic formulas until better ones are figured out.
		this->base_hp_ += std::lround( (this->bonus_hp_+1.05)*13.0);
		this->base_str_ += std::lround( (this->bonus_str_+1.05)*4.0);
		this->base_def_ += std::lround( (this->bonus_def_+1.05)*3.0);
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;

	}

	void add_gold(unsigned int gold){
		this->gold_ += gold;
	}

	void sub_gold(unsigned int gold){
		//checks will be handled by the shop functions for now.
		this->gold_ -= gold;
	}

	/**
	 *
	 * @param xp The amount of XP to add.
	 * @return True if player leveled up false otherwise.
	 */
	bool add_xp(unsigned int xp){
		//might make this just be a one-time calculation and store the value as a property but that's up in the air.
		double dl = static_cast<double>(this->lvl_+1);
		unsigned int mkxp = (dl * ((dl*0.79)*1.2) );
		unsigned int xp_lvl = std::lround( ( (dl*1.125) * mkxp )*1.6);
		this->xp_ += xp;
		if(this->xp_ > xp_lvl){
			this->level_up();
			return true;
		}
		else{
			return false;
		}
	}
	friend void show_all_stats(Player &);

};
void show_all_stats(Player &player){
	std::cout << "Name:'" << player.name_ + "' hp:" << player.base_hp_ << " str: "
			  << player.base_str_ << " def:" << player.base_def_ << " level:" << std::to_string(player.lvl_) <<
			  std::endl << "base hp:" << player.bonus_hp_ << " base str:" <<
			  player.bonus_str_ << " base def:" << player.bonus_def_
			  << " xp:" << player.xp_ << " gold: " << player.gold_
			  << std::endl;
}

#endif //ITP298_CAPSTONE_PLAYER_HXX
