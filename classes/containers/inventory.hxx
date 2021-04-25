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
#include <deque>
#include "../items/itembase.hxx"
#include "../items/weapon.hxx"
#include "../items/armor.hxx"

struct InventoryMenuTuple{
	std::string item_name;
	uint_fast32_t item_quantity;
	uint_fast32_t item_value;
};

class Inventory {
  private:
  protected:
	//The list of items contained in this object.
	std::unordered_map<uint_fast16_t, Item*> items;
  	//the number of items that are contained.
	std::unordered_map<uint_fast16_t, uint_fast32_t> item_quantity;
	//the indexes of the items as they are held in memory
	std::deque<uint_fast16_t> item_indexes;
	uint_fast16_t num_items;

  public:
	Inventory(std::vector<Item*> item={}, std::vector<uint_fast32_t> counts={}){
		if(item.size() != 0){
			uint_fast32_t i=0;
			for(auto el:item){
				this->items[el->get_id()] = el;
				this->item_indexes.push_back(el->get_id());
			}
			if(counts.size() != 0){
				for(auto item_id:this->item_indexes){
					this->item_quantity[item_id] = counts[i++];
				}
			}
			else{
				for(auto item_id:this->item_indexes){
					this->item_quantity[item_id] = 1;
				}
			}
		}
		this->num_items = items.size();
	}

	void add_item(Item &item, uint_fast16_t number=1){
		if(this->items.count(item.get_id()) != 0){
			this->item_quantity[item.get_id()]+=number;
		}
		else {
			this->items[item.get_id()] = &item;
			this->item_quantity[item.get_id()] = number;
			this->item_indexes.push_back(item.get_id());
			this->num_items++;
		}
	}

	Item *get_item(uint_fast16_t item_id) const{
		return this->items.at(item_id);
	}

	void add_at(unsigned short idx,uint_fast16_t num=1){
		if(idx > this->num_items)
			return;
		uint_fast16_t item_id = this->item_indexes[idx];

		this->item_quantity[item_id]+=num;
	}

	void remove_at(unsigned short idx, uint_fast16_t num=1){
		if(idx > this->num_items)
			return;
		uint_fast16_t item_id = this->item_indexes[idx];
		if(this->item_quantity[item_id] <= num) {
			this->items.erase(item_id);
			this->item_quantity.erase(item_id);
			this->item_indexes.erase(this->item_indexes.begin()+idx);
		}
		else
			this->item_quantity[item_id]-=num;
	}


	/**
	 * Removes an item from the inventory.
	 *
	 * @param item_id The id of the item
	 * @param num The amount to remove
	 * @return Whether there is any left.
	 */
	bool remove_item(unsigned short item_id,uint_fast16_t num=1){
		if(this->item_quantity[item_id] <= num) {
			this->items.erase(item_id);
			this->item_quantity.erase(item_id);
			//have to iterate over the deq to find the index of the item id we're removing.
			for(uint_fast16_t idx=0;idx<this->num_items;idx++){
				//once found remove it.
				if(this->item_indexes[idx] == item_id){
					this->item_indexes.erase(this->item_indexes.begin()+idx);
					break;
				}
			}
			//reduce the number of items.
			this->num_items--;
			//say we removed something.
			return true;
		}
		else{
			this->item_quantity[item_id]-=num;
			return false;
		}
	}

	bool remove_item(Item &item, uint_fast16_t num=1){
		return this->remove_item(item.get_id(),num);
	}

	unsigned short get_item_id(unsigned short idx) const{
		return this->item_indexes[idx];
	}
	unsigned int get_quantity(unsigned short item_id) const{
		return this->item_quantity.at(item_id);
	}
	bool contains(unsigned short item_id){
		return this->items.count(item_id) != 0;
	}
	std::deque<uint_fast16_t> get_item_ids() const{
		return this->item_indexes;
	}

	unsigned int number_items(){
		return this->item_indexes.size();
	}
	/**
	 *
	 * @return The object transformed into a string.
	 */
	virtual operator std::string() const{
		std::stringstream ss;
		ss << "Inventory [";
		uint_fast32_t i=0;
		for(auto el: this->items){
			ss << "{" << el.second->get_name() << ", " << this->item_quantity.at(el.first) << "}";
			if(++i < this->num_items){
				ss << ", ";
			}
		}
		ss << "] \nTotal Items:" << this->num_items << "\nItem Indexes = {";
		for(auto item_id: this->item_indexes){
			ss << item_id;
			if(--i > 0)
				ss << ", ";
		}
		ss << "}";
		return ss.str();
	}

	/**
	 *
	 * @return The number of items contained in the inventory.
	 */
	uint_fast16_t inventory_quantity() const{
		return this->num_items;
	}

	~Inventory(){
		this->items.clear();
		this->item_quantity.clear();
		this->item_indexes.clear();
	}
	friend std::ostream& operator <<(std::ostream &os, Inventory &inv);
};

std::ostream& operator<<(std::ostream &os, Inventory &inv) {
	os << "Format ({Item Name}, {Item Quantity})" << std::endl << (std::string) inv;
	return os;
}


#endif //ITP298_CAPSTONE_INVENTORY_HXX
