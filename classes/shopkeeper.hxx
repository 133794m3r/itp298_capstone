/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/

#ifndef ITP298_CAPSTONE_SHOPKEEPER_HXX
#define ITP298_CAPSTONE_SHOPKEEPER_HXX
#include <utility>
#include "fighters/player.hxx"
#include "containers/shop_inventory.hxx"
class ShopKeeper {
  private:
	ShopInventory shop_inventory_;
	std::string name_;
	Player *player_ = nullptr;
  public:
	explicit ShopKeeper(std::string name = "Shop Keep", const std::vector<Item*> &items = {},
					 const std::vector<unsigned int> &quantity = {}){
		this->shop_inventory_ = ShopInventory(items,quantity);
		this->name_ = std::move(name);
	}

	bool purchase_item(unsigned short item_id,unsigned int quantity=1){
		if(player_ == nullptr)
			return false;
		unsigned int cost = this->shop_inventory_.purchase_cost(item_id,quantity);
		if(cost > player_->get_gold()) {
			return false;
		}
		player_->sub_gold(cost);
		player_->add_item(*this->shop_inventory_.get_item(item_id),quantity);
		this->shop_inventory_.remove_item(item_id,quantity);
		return true;
	}

	const std::deque<unsigned short> list_inventory() const{
		return this->shop_inventory_.get_item_ids();
	}
	std::string get_name() const{
		return this->name_;
	}

	/**
	 * Retruns a std::vector of tuples of the Items in the shop's inventory.
	 * Each tuple is of the order of {Item.get_name(), Item_quantity, Item.get_value()}
	 * @return The result vector of the shop's inventory.
	 */
	std::vector<menu_item_data> show_inventory() const{
		std::vector<menu_item_data> item_results;
		item_results.reserve(this->shop_inventory_.inventory_quantity());
		for(auto item_id:this->list_inventory()){
			Item *item = this->shop_inventory_.get_item(item_id);
			item_results.push_back({item->get_name(), this->shop_inventory_.get_quantity(item_id), item->get_value()});
		}
		return item_results;
	};
	void enter_shop(Player &player){
		this->player_ = &player;
	}

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

	bool sell_item(unsigned short item_id, unsigned int amount=1){
		if(this->player_->player_inventory.get_quantity(item_id) < amount)
			return false;
		else if(!this->player_->player_inventory.contains(item_id))
			return false;

		unsigned int gold = this->sell_value(item_id,amount);
		this->player_->add_gold(gold);
		this->shop_inventory_.add_item(*this->player_->player_inventory.get_item(item_id), amount);
		this->player_->remove_item(item_id,amount);
		return true;
	}

};


#endif //ITP298_CAPSTONE_SHOPKEEPER_HXX
