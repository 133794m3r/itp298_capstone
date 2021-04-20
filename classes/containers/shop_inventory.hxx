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
class ShopInventory: public Inventory {
  public:
	bool purchase_item(unsigned_short item_id, unsigned int amount=1){
		return true;
	}
};


#endif //ITP298_CAPSTONE_SHOP_INVENTORY_HXX
