/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/

#ifndef ITP298_CAPSTONE_SHOPKEEPER_HXX
#define ITP298_CAPSTONE_SHOPKEEPER_HXX
#include <utility>

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

	bool purchase_item(unsigned short item_id,unsigned int quantity){
		unsigned int cost = this->shop_inventory_.purchase_cost(item_id,quantity);
		if(cost > player_->get_gold()) {
			return false;
		}
		player_->sub_gold(cost);
		player_->a
	}

	void enter_shop(Player &player){
		this->player_ = &player;
	}

	void exit_shop(){
		this->player_ = nullptr;
	}
};


#endif //ITP298_CAPSTONE_SHOPKEEPER_HXX
