/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/19/21.
*
*/

#ifndef ITP298_CAPSTONE_SHOP_INVENTORY_HXX
#define ITP298_CAPSTONE_SHOP_INVENTORY_HXX
#include "inventory.hxx"
#include "../../includes.hxx"
class ShopInventory: public Inventory {
  public:
	explicit ShopInventory(std::vecotr<){

	}
	/**
	 * The cost to buy amount of the items.
	 * @param item_id The item we're going to be using.
	 * @param amount The amount to attempt to purchase
	 * @return The amount of gold it'd cost to buy it.
	 */
	unsigned int purchase_cost(unsigned short item_id, unsigned int amount=1){
		return this->items[item_id]->get_value() * amount;
	}

	/**
	 * The value of the items to be sold. Always less than their value.
	 * @param item_id The id of the item we're going to be selling.
	 * @param amount
	 * @return
	 */
	unsigned int sell_value(Inventory &inv, unsigned short item_id, unsigned int amount=1){
		return std::lround(inv->purchase_cost(item_id,amount)*0.75);
	}
};


#endif //ITP298_CAPSTONE_SHOP_INVENTORY_HXX
