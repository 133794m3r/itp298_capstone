/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/

#ifndef ITP298_CAPSTONE_SHOP_KEEPER_HXX
#define ITP298_CAPSTONE_SHOP_KEEPER_HXX
#include <utility>
#include "fighters/player.hxx"
#include "containers/shop_inventory.hxx"
class ShopKeeper {
  private:
	ShopInventory shop_inventory_;
	std::string name_;
	Player *player_ = nullptr;
  public:
	//constructor is explicit since it can be called w/ no arguments
	explicit ShopKeeper(std::string name = "Shop Keep", const std::vector<Item*> &items = {},
					 const std::vector<unsigned char> &quantity = {}){
		//set the inventory to the correct items
		this->shop_inventory_ = ShopInventory(items,quantity);
		//make sure set the name
		this->name_ = std::move(name);
	}

	/**
	 * Purchase an item from the shop
	 * @param item_id The id of the item to purchase
	 * @param quantity how many to purchase
	 * @return if the player was able to purchase said item.
	 */
	bool purchase_item(unsigned short item_id,unsigned short quantity=1){
		//if there's not yet a player bail b4 sigint/sigfault/etc.
		if(player_ == nullptr)
			return false;
		//get the cost
		unsigned int cost = this->shop_inventory_.purchase_cost(item_id,quantity);
		//see if they can
		if(cost > player_->get_gold()) {
			return false;
		}
		//subtract the gold
		player_->sub_gold(cost);
		//ad the item to the player's inventory
		player_->add_item(*this->shop_inventory_.get_item(item_id),quantity);
		//remove the item from the shop's inventory
		this->shop_inventory_.remove_item(item_id,quantity);
		return true;
	}

	/**
	 * utility function to give me ids of all items.
	 * @return the ids of all items in the shop
	 */
	std::deque<unsigned short> list_inventory() const{
		return this->shop_inventory_.get_item_ids();
	}

	//standard getter
	std::string get_name() const{
		return this->name_;
	}

	/**
	 * Returns a std::vector of tuples of the Items in the shop's inventory.
	 * Each tuple is of the order of {Item.get_name(), Item_quantity, Item.get_value()}
	 * @return The result vector of the shop's inventory.
	 */
	std::vector<menu_item_data> show_inventory() const{
		std::vector<menu_item_data> item_results;
		item_results.reserve(this->shop_inventory_.inventory_quantity());
		//iterate over the items and then return a vector of the items with the values we need.
		for(auto item_id:this->list_inventory()){
			Item *item = this->shop_inventory_.get_item(item_id);
			item_results.push_back({item->get_name(), this->shop_inventory_.get_quantity(item_id), item->get_value()});
		}
		return item_results;
	};

	//have the player enter the shop
	void enter_shop(Player &player){
		this->player_ = &player;
	}

	//have the player exit the shop
	void exit_shop(){
		this->player_ = nullptr;
	}

	/**
	 * The value of the items to be sold. Always less than their value.
	 * @param item_id The id of the item we're going to be selling.
	 * @param amount
	 * @return
	 */
	unsigned int sell_value(unsigned short item_id, unsigned int amount=1) const{
		return std::lround(this->player_->player_inventory.get_item(item_id)->get_value()*0.75*amount);
	}

	/**
	 * Let's the player sell one of their items.
	 * @param item_id The item's id.
	 * @param amount The amount to sell.
	 * @return Whether they could or not.
	 */
	bool sell_item(unsigned short item_id, unsigned char amount=1){
		//bail
		if(this->player_ == nullptr)
			return false;

		//if they don't have the item
		if(!this->player_->player_inventory.contains(item_id) ||
		   this->player_->player_inventory.get_quantity(item_id) < amount)
			return false;

		//ok let's figure out how much to award them for the sale.
		unsigned int gold = this->sell_value(item_id,amount);
		//add the gold
		this->player_->add_gold(gold);
		//add the item to the shop's inventory
		this->shop_inventory_.add_item(*this->player_->player_inventory.get_item(item_id), amount);
		//remove the item from player's inventory
		this->player_->remove_item(item_id,amount);
		return true;
	}

};


#endif //ITP298_CAPSTONE_SHOP_KEEPER_HXX
