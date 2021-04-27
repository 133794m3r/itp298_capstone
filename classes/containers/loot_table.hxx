/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/25/21.
*
*/

#ifndef ITP298_CAPSTONE_LOOT_TABLE_HXX
#define ITP298_CAPSTONE_LOOT_TABLE_HXX
#include <utility>
#include <vector>
#include "../../random.h"
#include "inventory.hxx"

class LootTable:public Inventory {
  private:
	std::vector<unsigned int> chances;
  public:
	explicit LootTable(std::vector<Item*> items={}, std::vector<unsigned int> counts={},const std::vector<double>& probs = {})
	:Inventory(std::move(items),std::move(counts)){
		this->chances.reserve(probs.size());
		for(double prob:probs){
			this->chances.push_back(std::lround(prob*4294967295));
		}
	}

	std::vector <std::pair<Item*,unsigned int>> award_items(){
		//create a temporary vector
		std::vector<std::pair<Item *,unsigned int>> rewards;
		unsigned int res = 0;
		unsigned short item_id = 0;
		//see which items we'll give them
		for(unsigned int i=0;i<this->item_indexes.size();i++){
			res = xorshift128(0,4294967295);
			//if it's less than the probability we award it.
			if(res <= this->chances[i]){
				//first have to get the item's id.
				item_id = this->item_indexes[i];
				//then we add a std::pair to the vector
				rewards.push_back(std::make_pair(this->items[item_id],this->item_quantity[item_id]));
			}
		}
		return rewards;
	}

	void add_item(Item &item,unsigned int quantity,double probability){
		this->chances.push_back(std::lround(probability*4294967295));
		Inventory::add_item(item,quantity);
	}
};


#endif //ITP298_CAPSTONE_LOOT_TABLE_HXX