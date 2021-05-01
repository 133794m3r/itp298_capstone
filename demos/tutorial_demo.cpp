/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/28/21.
*
*/
#include "../menus/battle.hxx"
#include "../menus/inventory_menu.hxx"
#include "../menus/shop.hxx"
#include "../data/items.hxx"
#include "../data/mobs.hxx"
#include "../data/shops.hxx"
#include "../data/menus.hxx"
#include "../menus/tutorial_menu.hxx"
int main(){
	std::cout << "\x1b[" << BLACK_BG << "m\x1b[" << BRIGHT_WHITE_TXT << "m";
	Player player("Jimbo");
	InventoryMenu inv_men(&player);
	TutorialMenu tut_menu(player,inv_men);
	tut_menu.enter();
	return 0;
}
