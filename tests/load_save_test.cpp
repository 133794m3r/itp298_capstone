/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/30/21.
*
*/
#include "../classes/items/item_base.hxx"
#include "../classes/items/weapon.hxx"
#include "../classes/items/armor.hxx"
#include "../classes/items/potion.hxx";
#include "../data/items.hxx"
#include "../classes/fighters/player.hxx"
#include "../main.hxx"
int main(){
	Player player("zzz_test_user");
	player.add_item(stick);
	save_game(player);
	Player player2 = load_game("zzz_test_user_save_file.dat");
	std::cout << (std::string) player2 << std::endl;
	int i =1;
}