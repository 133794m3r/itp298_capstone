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
#include "../items/weapon.hxx"
#include "../items/armor.hxx"
class Inventory {
  private:
  protected:
	std::unordered_map<unsigned short, Item*> items;
	std::unordered_map<unsigned short, uint_fast32_t> item_quantity;
	uint_fast16_t num_items;

  public:
	Inventory(std::vector<Item*> item={}, std::vector<uint_fast32_t> counts={}){
		if(item.size() != 0){
			uint_fast32_t i=0;
			if(counts.size() != 0){
				for(auto el:item){
					this->items[el->get_id()] = el;
					this->item_quantity[el->get_id()] = counts[i++];
				}
			}
			else{
				for(auto el:item){
					this->items[el->get_id()] = el;
					this->item_quantity[el->get_id()] = 1;
				}
			}
		}
		this->num_items = items.size();
	}

	void add_item(Item &item, uint_fast32_t number=1){
		if(this->items.count(item.get_id()) != 0){
			this->item_quantity[item.get_id()]+=number;
		}
		else {
			this->items[item.get_id()] = &item;
			this->item_quantity[item.get_id()] = number;
			this->num_items++;
		}
	}

	//remove an item based upon it's index in the inventory.
	bool remove_item(unsigned short item_id){
		if(this->items.count(item_id) != 0) {
			this->items.erase(item_id);
			this->item_quantity.erase(item_id);
			this->num_items--;
			return true;
		}
		else{
			this->item_quantity[item_id]--;
			return false;
		}
	}

	operator std::string(){
		std::stringstream ss;
		ss << "Inventory [";
		uint_fast32_t i=0;
		for(auto el: this->items){
			ss << "{" << el.second->get_name() << ", " << this->item_quantity[el.first] << "}";
			if(++i < this->num_items){
				ss << ", ";
			}
		}
		ss << "] " << std::endl <<  "Total Items:" << this->num_items;
		return ss.str();
	}

	uint_fast16_t inventory_quantity(){
		return this->num_items;
	}

	~Inventory(){
		items.clear();
		item_quantity.clear();
	}
	friend std::ostream& operator <<(std::ostream &os, Inventory &inv);
};

std::ostream& operator<<(std::ostream &os, Inventory &inv) {
	os << "Format ({Item Name}, {Item Quantity})" << std::endl << (std::string) inv;
	return os;
}


#endif //ITP298_CAPSTONE_INVENTORY_HXX
