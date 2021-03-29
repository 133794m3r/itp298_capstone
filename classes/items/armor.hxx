#ifndef ITP298_CAPSTONE_ARMOR_HXX
#define ITP298_CAPSTONE_ARMOR_HXX
#include <string>
#include "itembase.hxx"

class Armor: public Item {
  private:
	enum types{weapon=0,armor=1};
	char type;
  public:
	std::string name;
	explicit Item(){
		this->type = 0;
		this->name = "";
	}
	Item(char type=0,std::string name=""){
		this->type = type;
		this->name = name;
	}

	~Item(){

	}
};


#endif //ITP298_CAPSTONE_ARMOR_HXX
