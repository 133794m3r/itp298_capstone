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
	test.add_item(sword,5);
	test.add_item(club,3);
	test.add_item(plaid_shirt,2);
	std::cout << (std::string) test << std::endl;
	test.remove_item(shirt.get_id());
	std::cout << (std::string) test << std::endl;
	return 0;
}