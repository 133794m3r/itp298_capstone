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
	Inventory test;
	//create some items to put in the inventory
	Weapon sword("Sword");
	Armor shirt("Shirt");
	Item stick("Stick");
	Weapon club("Club");
	Armor plaid_shirt("Plaid Shirt");
	test.add_item(sword,1);
	test.add_item(shirt, 1);
	test.add_item(stick,3);
	test.add_item(sword,5);
	test.add_item(club,3);
	test.add_item(plaid_shirt,2);
	test.remove_item(shirt.get_id());
	test.add_at(2,3);
	test.remove_at(1);
	std::cout << (std::string) test << std::endl;

	if( (std::string) test != "Inventory [{Plaid Shirt, 2}, {Club, 6}, {Stick, 2}, {Sword, 6}] \nTotal Items:4\nItem Indexes = {0, 2, 3, 4}"){
		std::cout << "Inventory test failed got '" << (std::string) test << "' but expected  'Inventory [{Plaid Shirt, 2}, {Club, 6}, {Stick, 2}, {Sword, 6}] \nTotal Items:4\nItem Indexes = {0, 2, 3, 4} '" << std::endl;
		return 1;
	}
	return 0;
}