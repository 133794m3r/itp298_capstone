/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/22/21.
*
*/

#include "../classes/shopkeeper.hxx"
int main(){
	//test file for the shop current WIP
	//create player
	Player test_player("Jim");
	//add some gold
	test_player.add_gold(100);
	//create some items
	Armor shirt("T-shirt");
	Weapon sword("Sword");
	Item rock("Rock");
	//create shop keeper
	ShopKeeper shop_keeper("Kennel Club",{&shirt,&sword,&rock},{1,1,1});
	//make player enter the shop
	shop_keeper.enter_shop(test_player);

	return 0;
}
