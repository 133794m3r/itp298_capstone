/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/
#ifndef ITP298_CAPSTONE_PLAYER_HXX
#define ITP298_CAPSTONE_PLAYER_HXX
class ShopKeeper;
class InventoryMenu;
#include <utility>
#include <fstream>

#include "actor.hxx"
#include "../containers/inventory.hxx"
#include "../items/potion.hxx"

class Player: public Actor {
  private:
	//player has their current xp and gold properties atm.
	unsigned int xp_;
	unsigned int gold_;
	Inventory player_inventory;
	unsigned short current_game_level;
  public:
	//initialize the Player class with the defined properties and using the parent classes' constructor for shared properties.
	/**
	 *
	 * @param name
	 * @param level
	 * @param bonus_hp
	 * @param bonus_str
	 * @param bonus_def
	 * @param xp
	 * @param gold
	 */
	explicit Player(std::string name="Player", unsigned short level=1,double bonus_hp=0.05,
				 double bonus_str=0.05, double bonus_def=0.05,unsigned int xp=0, unsigned int gold = 100,unsigned short current_level=0)
				 :Actor(std::move(name),level,bonus_hp, bonus_str,bonus_def,20,
			5,4,255){
		//player will always have a set id that's way higher than the rest of the objects in the world.
		this->id = 65535;
		this->gold_ = gold;
		this->xp_ = xp;
		this->current_game_level = current_level;
		Player::set_level(level);
	}
	/**
	 * Sets the player's level
	 * @param level The level to set the player to
	 */
	void set_level(unsigned short level) override{

		int dif;
		//if it's the same just do nothing.
		if(level == this->lvl_)
			dif = this->lvl_ - 1;
		else if(level > this->lvl_)
			dif = level - this->lvl_;
		else
			dif = this->lvl_ - level;
		//when they modify the level change the stats to the proper values.
		this->base_hp_ += std::lround( (this->bonus_hp_+1.05)*13.0*dif);
		this->base_str_ += std::lround( (this->bonus_str_+1.05)*4.0*dif);
		//increase hardiness against mobs
		this->base_def_ += std::lround( (this->bonus_def_+1.05)*3.25*dif);
		//then set the current stats from the base.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}
	//level up actor with new stats
	void level_up(){
//		unsigned int old_hp = this->base_hp_;
//		unsigned int old_str = this->base_str_;
//		unsigned int old_def = this->base_def_;
		//basic formulas until better ones are figured out.
		this->base_hp_ += std::lround( (this->bonus_hp_+1.05)*13.0);
		this->base_str_ += std::lround( (this->bonus_str_+1.05)*4.0);
		//to make them hardier when it comes to fighting mobs
		this->base_def_ += std::lround( (this->bonus_def_+1.05)*3.25);
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;

	}

	/**
	 * Gets the player's gold
	 * @return the amount of gold the player has.
	 */
	unsigned int get_gold() const{
		return this->gold_;
	}

	//adds gold to the player
	void add_gold(unsigned int gold){
		this->gold_ += gold;
	}

	//removes gold
	void sub_gold(unsigned int gold){
		//checks will be handled by the shop functions for now.
		this->gold_ -= gold;
	}

	/**
	 * Adds XP to the player and levels up if necessary
	 * @param xp The amount of XP to add.
	 * @return True if player leveled up false otherwise.
	 */
	bool add_xp(unsigned int xp){
		//might make this just be a one-time calculation and store the value as a property but that's up in the air.
		auto dl = this->lvl_ + 1.00;
		unsigned long mkxp = std::lround((dl * ((dl*0.79)*1.2) ));
		unsigned int xp_lvl = std::lround( ( (dl*1.125)* mkxp)*1.6);
		this->xp_ += xp;
		if(this->xp_ > xp_lvl){
			this->lvl_++;
			this->level_up();
			return true;
		}
		else{
			return false;
		}
	}

	//add HP to the player
	unsigned short add_hp(unsigned short hp){
		unsigned short restored;
		if(hp > (this->base_hp_ - this->hp_)) {
			restored = this->base_hp_ - this->hp_;
			this->hp_ = this->base_hp_;
		}
		else {
			restored = hp;
			this->hp_ += hp;
		}
		return restored;
	}
	//item removal functions
	void remove_item(unsigned short item_id, unsigned short num = 1){
		this->player_inventory.remove_item(item_id, num);
	}

	void remove_item(Item &item, unsigned short num = 1){
		this->player_inventory.remove_item(item, num);
	}

	//add an item. Has to have an actual item in case it doesn't already exist in inventory.
	void add_item(Item &item, unsigned char num = 1){
		this->player_inventory.add_item(item,num);
	}

	//unequip the armor
	void unequip_armor() override{
		if(this->armor_equipped == nullptr)
			return;
		//add it to the player's inventory
		this->player_inventory.add_item(*this->armor_equipped,1);
		//then actually unequip it
		Actor::unequip_armor();
	}

	//same with the weapon
	void unequip_weapon() override{
		if(this->weapon_held == nullptr)
			return;
		this->player_inventory.add_item(*this->weapon_held,1);
		Actor::unequip_weapon();
	}

	//get the player's xp
	unsigned int get_xp() const{
		return this->xp_;
	}

	//get the potions from the player's inventory, also how many they have. value is used for the power of the potion.
	std::vector<std::pair<menu_item_data, unsigned short> > get_potions() const{
		//create my vector
		std::vector<std::pair<menu_item_data, unsigned short> > potions;
		//iterate over the item ids
		for(auto item_id:this->player_inventory.get_item_ids()){
			//get the item
			Item *item = this->player_inventory.get_item(item_id);
			//if it's a potion add it to the list
			if(item->get_type() == 3){
				//first recast it.
				auto *pot = dynamic_cast<Potion *>(item);
				potions.push_back({{item->get_name(),player_inventory.get_quantity(item_id),pot->get_power()},item->get_id()});
			}
		}
		return potions;
	}

	std::vector<menu_item_data> show_inventory(){
		std::vector<menu_item_data> item_results;
		item_results.reserve(this->player_inventory.inventory_quantity());
		for(auto item_id:this->player_inventory.get_item_ids()){
			Item *item = this->player_inventory.get_item(item_id);
			item_results.push_back({item->get_name(),
									this->player_inventory.get_quantity(item_id),
									static_cast<unsigned int>(item->get_value()*0.75)
								   });
		}
		return item_results;
	}

	std::deque<unsigned short> list_inventory() const{
		return this->player_inventory.get_item_ids();
	}

	explicit operator std::string() const override{
		std::stringstream ss;
		ss << "id: " << this->id << " " << this->name_ << " hp:" <<this->hp_ << "/" << this->base_hp_ <<
			" str:" << this->str_ << "/" << this->base_str_ << " def:" << this->def_ << "/"
			<< this->base_def_ << " xp:" << this->xp_ << " g:" << this->gold_;
		return ss.str();
	}


	friend void show_all_stats(Player &player);
	friend std::ostream& operator<<(std::ostream &, Player &);
	//for now till I make it work the way I want.
	friend ShopKeeper;
	friend InventoryMenu;

	friend void save_game(const Player &);
	friend int load_game(const std::string& save_file,Player &);
	friend void add_items_(Player &, const std::string&);
};

void show_all_stats(Player &player){
	std::cout << "Name:'" << player.name_ + "' hp:" << player.base_hp_ << " str: "
			  << player.base_str_ << " def:" << player.base_def_ << " level:" << std::to_string(player.lvl_) <<
			  std::endl << "base hp:" << player.bonus_hp_ << " base str:" <<
			  player.bonus_str_ << " base def:" << player.bonus_def_
			  << " xp:" << player.xp_ << " gold: " << player.gold_
			  << std::endl;
}

std::ostream& operator<<(std::ostream &os, Player &a) {
	os << a.name_ << " hp:" << a.hp_ << "/" << a.base_hp_ << " str:" << a.str_ << "/"
	   << a.base_str_ << " def:" << a.def_ << "/" << a.base_def_
	   << " xp:" << a.xp_ << " g:" << a.gold_;
	return os;
}
#endif //ITP298_CAPSTONE_PLAYER_HXX
