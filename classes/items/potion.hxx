/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/28/21.
*
*/

#ifndef ITP298_CAPSTONE_POTION_HXX
#define ITP298_CAPSTONE_POTION_HXX

#include <utility>
#include "../../includes.hxx"
#include "item_base.hxx"
class Potion:public Item {
  private:
	unsigned short power_;
  public:
	//the name should always convey that it's a potion
	explicit Potion(std::string name="Junk", unsigned short level=1, unsigned short tier=1):Item(std::move(name)+" Pot",3,tier,level){
		this->power_ = std::lround((level*16.00)*((tier+1.00)/4.00));
	}
	unsigned short get_power(){
		return this->power_;
	}
};


#endif //ITP298_CAPSTONE_POTION_HXX
