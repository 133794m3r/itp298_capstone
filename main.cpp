/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include <iostream>
#include "classes/items/weapon.hxx"
#include "classes/items/armor.hxx"
#include "classes/items/potion.hxx"
#include "classes/fighters/mob.hxx"
#include "classes/fighters/player.hxx"
#include "data/maps.hxx"
#include "data/mobs.hxx"
#include "data/items.hxx"
#include "data/shops.hxx"
#include "menus/map_movement.hxx"
#include "menus/battle.hxx"
#include "menus/shop.hxx"
#include "menus/inventory_menu.hxx"
#include "menus/tutorial_menu.hxx"
int main() {
	std::cout << "\x1b[" << BRIGHT_WHITE_TXT << ";" << BLACK_BG << "m";
	std::string padding_string(53,' ');

	std::cout << "Welcome to the world of Dangling Pointers, where adventure awaits!\n\n\n";

	//draw text-box
	std::cout << "+------------------------------------------------------+"
			  << "\n| 1) Start a new Game 2) Load a saved game" << padding_string.substr(0,13) << "|\n"
			  << "| 3) Exit the game" << padding_string.substr(0,37) << "|\n" << "+------------------------------------------------------+" << std::endl;
	unsigned int option;
	std::cout << "\x1b[1mSelection\x1b[22m: ";
	option = valid_option(1,3);
	if(option == 1) {
		std::string player_name;
		std::cout << "Enter your name: ";
		std::cin >> player_name;
		Player player(player_name);
		InventoryMenu player_inv(&player);
		TutorialMenu tutorial(player, player_inv);
		tutorial.enter();
	}
	//not yet implemented
	else if(option == 2){
		std::cout << "not yet implemented";
		return 1;
	}
	else{
		return 0;
	}
}
