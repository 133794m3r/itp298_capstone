/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/22/21.
*
*/

#include "../classes/shopkeeper.hxx"
int main(){
	Player test_player("Jim");
	test_player.add_gold(10000);
	Armor shirt("T-shirt");
	Weapon sword("Sword");
	Item rock("Rock");
	ShopKeeper shop_keeper("Kennel Club",{&shirt,&sword,&rock},{1,1,1});
	shop_keeper.enter_shop(test_player);

	return 0;
}
