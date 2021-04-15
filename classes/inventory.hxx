/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/

#ifndef ITP298_CAPSTONE_INVENTORY_HXX
#define ITP298_CAPSTONE_INVENTORY_HXX
#include <vector>
#include <sstream>
#include "items/itembase.hxx"

class Inventory {
  private:
	//
  protected:
	//will probably make these a doubly ended queue if I had more time.
	std::vector<Item*> items;
	std::vector<uint_fast32_t> item_quantity;
	uint_fast16_t num_items;

  public:
	Inventory(std::vector<Item*> item={}, std::vector<uint_fast32_t> quantity={}){
		this->items = item;
		this->item_quantity = quantity;
		this->num_items = items.size();
	}

	void add_item(Item &item, uint_fast32_t quantity){
		this->items.push_back(&item);
		this->item_quantity.push_back(quantity);
		this->num_items++;
	}

	//remove an item based upon it's index in the inventory.
	bool remove_item(uint_fast16_t idx){
		if(this->item_quantity[idx] == 1){
			this->items.erase(items.begin()+idx);
			this->item_quantity.erase(item_quantity.begin()+idx);
			num_items--;
			return true;
		}
		else{
			this->item_quantity[idx]--;
			return false;
		}
	}

	~Inventory(){
		items.clear();
		item_quantity.clear();
	}
};


#endif //ITP298_CAPSTONE_INVENTORY_HXX
