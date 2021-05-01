/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/12/21.
*
*/
#include "../includes.hxx"
#include "../classes/containers/inventory.hxx"
int main(){
	//the basic test file
	Inventory test;
	//create some items to put in the inventory
	Weapon sword("Sword");
	Armor shirt("Shirt");
	Item stick("Stick");
	Weapon club("Club");
	Armor plaid_shirt("Plaid Shirt");
	//add them to the inventory
	test.add_item(sword,1);
	test.add_item(shirt, 1);
	test.add_item(stick,3);
	test.add_item(sword,5);
	test.add_item(club,3);
	test.add_item(plaid_shirt,2);
	//remove some item
	test.remove_item(shirt.get_id());
	//add 3 more at index 2
	test.add_at(2,3);
	//remove 1 at index 1
	test.remove_at(1);
	//show the stringified version
	std::cout << (std::string) test << std::endl;

	//make sure it's the same. This is platform dependent due to the hashing function apparently.
	if( (std::string) test !=
#ifdef _WIN32
    "Inventory [{Sword, 6}, {Stick, 2}, {Club, 6}, {Plaid Shirt, 2}] \nTotal Items:4\nItem Indexes = {0, 2, 3, 4}"){
#else
	"Inventory [{Plaid Shirt, 2}, {Club, 6}, {Stick, 2}, {Sword, 6}] \nTotal Items:4\nItem Indexes = {0, 2, 3, 4}"){
#endif
		std::cout << "Inventory test failed got '" << (std::string) test << "' but expected  'Inventory [{Plaid Shirt, 2}, {Club, 6}, {Stick, 2}, {Sword, 6}] \nTotal Items:4\nItem Indexes = {0, 2, 3, 4} '" << std::endl;
		//it didn't work and show the error
		return 1;
	}
	//return 0 for build systme
	return 0;
}