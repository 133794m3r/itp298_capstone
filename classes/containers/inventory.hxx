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
#include <unordered_map>
#include "../items/itembase.hxx"

class Inventory {
  private:
	//
  protected:
	//will probably make these a doubly ended queue if I had more time.
//	std::vector<Item*> items;
	std::unordered_map<unsigned short, Item*> items;
//	std::vector<uint_fast32_t> item_quantity;
	std::unordered_map<unsigned short, uint_fast32_t> item_quantity;
	uint_fast16_t num_items;

  public:
	Inventory(std::vector<Item*> item={}, std::vector<uint_fast32_t> counts={}){
		if(item.size() != 0){
			uint_fast32_t i=0;
			//commented out b/c I dont' have that method.
//			if(counts.size() != 0){
//				for(auto el:item){
//					this->items[el->get_id()] = el;
//					this->item_quantity[el->get_id()] = counts[i++];
//				}
//			}
//			else{
//				for(auto el:item){
//					this->items[el->get_id()] = el;
//					this->item_quantity[el->get_id()] = 1;
//				}
//			}
		}
		this->num_items = items.size();
	}

	void add_item(Item &item, uint_fast32_t number){
//		this->items.push_back(&item);
//		this->item_quantity.push_back(quantity);
		//commented out as I don't have these properties yet.
//		this->items[item.get_id()] = item;
//		this->item_quantity[item.get_id()] = number;
		this->num_items++;
	}

	//remove an item based upon it's index in the inventory.
	bool remove_item(unsigned short item_id){
//		if(this->item_quantity[idx] == 1){
//			this->items.erase(items.begin()+idx);
//			this->item_quantity.erase(item_quantity.begin()+idx);
//			num_items--;
//			return true;
//		}
//		else{
//			this->item_quantity[idx]--;
//			return false;
//		}
		if(this->items.count(item_id) != 0) {
			this->items.erase(item_id);
			this->item_quantity.erase(item_id);
		}
		else{
			this->item_quantity[item_id]--;
		}
	}

	~Inventory(){
		items.clear();
		item_quantity.clear();
	}
};


#endif //ITP298_CAPSTONE_INVENTORY_HXX
