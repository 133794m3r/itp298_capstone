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
  public:
	explicit ShopKeeper(std::string name = "Shop Keep", const std::vector<Item*> &items = {}, const std::vector<unsigned int> &quantity = {}){
		this->shop_inventory_ = ShopInventory(items,quantity);
		this->name_ = std::move(name);
	}
	bool purchase_item();
};


#endif //ITP298_CAPSTONE_SHOPKEEPER_HXX
