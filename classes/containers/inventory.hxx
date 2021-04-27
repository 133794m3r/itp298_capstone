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


//basic struct for use with the menus
struct InventoryMenuTuple{
	std::string item_name;
	unsigned int item_quantity;
	unsigned int item_value;
};

class Inventory {
  private:
	//no private data atm.
  protected:
	//The list of items contained in this object.
	std::unordered_map<unsigned short, Item*> items;
  	//the number of items that are contained.
	std::unordered_map<unsigned short, unsigned int> item_quantity;
	//the indexes of the items as they are held in memory
	std::deque<unsigned short> item_indexes;
	unsigned short num_items;

  public:
	//constructor
	Inventory(std::vector<Item*> item={}, std::vector<unsigned int> counts={}){
		if(item.size() != 0){
			unsigned int i=0;
			//basic loop to set all of the items up
			for(auto el:item){
				this->items[el->get_id()] = el;
				this->item_indexes.push_back(el->get_id());
			}
			//see if they set any counts.
			if(counts.size() != 0){
				//set quantities based upon what's given.
				for(auto item_id:this->item_indexes){
					this->item_quantity[item_id] = counts[i++];
				}
			}
			else{
				//otherwise set to 1.
				for(auto item_id:this->item_indexes){
					this->item_quantity[item_id] = 1;
				}
			}
		}
		//set the size to the total number.
		this->num_items = static_cast<unsigned short>(items.size());
	}

	/**
	 * Add an item to the Inventory
	 * @param item the item to add
	 * @param number The number to add
	 */
	void add_item(Item &item, unsigned short number=1){
		//if it already exists
		if(this->items.count(item.get_id()) != 0){
			//add to it that number
			this->item_quantity[item.get_id()]+=number;
		}
		else {
			//otherwise add an item to the hashtables/such.
			this->items[item.get_id()] = &item;
			this->item_quantity[item.get_id()] = number;
			this->item_indexes.push_back(item.get_id());
			//increment total
			this->num_items++;
		}
	}

	/**
	 * Gets an Item from the inventory.
	 *
	 * @param item_id Get the item by id.
	 * @return The pointer to the item.
	 */
	Item *get_item(unsigned short item_id) const{
		return this->items.at(item_id);
	}

	/**
	 * Adds an item as specific index
	 *
	 * @param idx
	 * @param num
	 */
	void add_at(unsigned short idx,unsigned short num=1){
		if(idx > this->num_items)
			return;
		unsigned short item_id = this->item_indexes[idx];

		this->item_quantity[item_id]+=num;
	}

	/**
	 * Removes an item at the specified index
	 * @param idx
	 * @param num
	 */
	void remove_at(unsigned short idx, unsigned short num=1){
		//if it's more than we have just exit. No time for throwing errors atm.
		if(idx > this->num_items)
			return;

		unsigned short item_id = this->item_indexes[idx];
		//if we're removing the amount or more than is there remove it from the variables.
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
	bool remove_item(unsigned short item_id,unsigned short num=1){
		if(this->item_quantity[item_id] <= num) {
			this->items.erase(item_id);
			this->item_quantity.erase(item_id);
			//have to iterate over the deq to find the index of the item id we're removing.
			for(unsigned short idx=0;idx<this->num_items;idx++){
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
			//it still exists
			this->item_quantity[item_id]-=num;
			return false;
		}
	}

	/**
	 *
	 * @param item Remove an item based upon that item.
	 * @param num Number to remove
	 * @return whether it was a success.
	 */
	bool remove_item(Item &item, unsigned short num=1){
		return this->remove_item(item.get_id(),num);
	}

	/**
	 * Get an item based upon an index
	 * @param idx
	 * @return
	 */
	unsigned short get_item_id(unsigned short idx) const{
		return this->item_indexes[idx];
	}

	/**
	 * Get an item based upon it's id
	 *
	 * @param item_id
	 * @return
	 */
	unsigned int get_quantity(unsigned short item_id) const{
		return this->item_quantity.at(item_id);
	}

	/**
	 * See if someone has an item based upon it's id.
	 * @param item_id
	 * @return
	 */
	bool contains(unsigned short item_id){
		return this->items.count(item_id) != 0;
	}

	/**
	 * Get all of the ids of all items that we have.
	 *
	 * @return
	 */
	std::deque<unsigned short> get_item_ids() const{
		return this->item_indexes;
	}

	/**
	 * Stringify the object.
	 *
	 * @return The object transformed into a string.
	 */
	virtual operator std::string() const{
		std::stringstream ss;
		ss << "Inventory [";
		unsigned int i=0;
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
	 *
	 * @return The number of items contained in the inventory.
	 */
	unsigned short inventory_quantity() const{
		return this->num_items;
	}

	//during desstructor clear it all.
	~Inventory(){
		this->items.clear();
		this->item_quantity.clear();
		this->item_indexes.clear();
	}

	//make sure we can send it to cout.
	friend std::ostream& operator <<(std::ostream &os, Inventory &inv);
};

std::ostream& operator<<(std::ostream &os, Inventory &inv) {
	os << "Format ({Item Name}, {Item Quantity})" << std::endl << (std::string) inv;
	return os;
}


#endif //ITP298_CAPSTONE_INVENTORY_HXX
