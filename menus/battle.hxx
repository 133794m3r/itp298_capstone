/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#ifndef ITP298_CAPSTONE_BATTLE_HXX
#define ITP298_CAPSTONE_BATTLE_HXX
#include "../includes.hxx"
#include "../classes/fighters/player.hxx"
#include "../classes/fighters/mob.hxx"
#include "inputs.hxx"

int battle(Player &player,Mob &mob){
	std::string options[4] = {
			"Attack",
			"Defend",
			"Item",
			"Wait"
	};

	unsigned int num_opts = sizeof options / sizeof options[0];
	unsigned int option = 0;
	unsigned int mob_opt;
	unsigned int dmg;

	/**
Battle UI Mockup. Will look something like this.
=========================================
Enemy
Lvl AAA XXXX/YYYY

	                                       Player
	                                  Lvl BBB XXXX/YYYY

+-----------------------------------------------------+
| 1) ATTACK        2) DEFEND         3) ITEM          |
| 4) WAIT          5) SOMETHING      6) ELSE          |
+-----------------------------------------------------+
Selection:
=============
Then if they have an invalid option it'll be
below the text box. For a message it'll be in that box.
If enemy's HP is over 4 digits then we make it be ????.
	 */
	// we only continue the battle as long as both participants are alive
	while(player.is_alive() && mob.is_alive()) {

		for (unsigned char i = 0; i < num_opts; i++) {
			std::cout << (int) i + 1 << " " << options[i] << std::endl;
		}

		option = valid_option(1,num_opts);
		//have the mob randomly select one for now.
		mob_opt = xorshift128(0, 3);
		//currently only doing the attack one
		if(option == 1) {
			dmg = player.attack(mob);
			std::cout << player.get_name() << " did " << dmg << " damage!" << std::endl;
		}
		//mobs can attack for now otherwise they do nothing that turn.
		if(mob_opt == 0) {
			dmg = mob.attack(player);
			std::cout << mob.get_name() << " did " << dmg << " damage!" << std::endl;
		}
		//reset the option to 0.
		option = 0;
	}
	//figure out who died
	if(player.is_alive())
		std::cout << player.get_name() << " defeated " << mob.get_name() << std::endl;
	else
		std::cout << player.get_name() << " was defeated by " << mob.get_name() << std::endl;
	return 0;
}
#endif //ITP298_CAPSTONE_BATTLE_HXX
