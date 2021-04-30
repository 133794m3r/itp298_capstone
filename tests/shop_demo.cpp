/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/22/21.
*
*/


#include "../classes/shop_keeper.hxx"
#include "../menus/shop.hxx"
int main(){
	//the demo files are always used for testing
	//make player
	Player test_player("Jim");
	//add some gold
	test_player.add_gold(100);
	//create some items
	Armor shirt("T-shirt");
	Weapon sword("Sword");
	Item rock("Rock");
	//create a new shop keeper add items
	ShopKeeper shop_keeper("Kennel Club",{&shirt,&sword,&rock},{1,1,1});
	//create shop menu
	ShopMenu shop_menu(shop_keeper, test_player);
	//run it
	shop_menu.shop_menu();
	//show a new line
	std::cout << std::endl;
	//always 0.
	return 0;
}