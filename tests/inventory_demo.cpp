/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/26/21.
*
*/
#include "../includes.hxx"
#include "../menus/inventory_menu.hxx"
int main(){
	Player player("Jim");
	Armor armor("Shirt");
	Weapon weapon("Sword");
	Potion potion;
	player.add_item(armor);
	player.add_item(weapon);
	player.add_item(potion);
	player.damage(7);
	InventoryMenu inv_menu(&player);
	inv_menu.enter();
	return 0;
}
