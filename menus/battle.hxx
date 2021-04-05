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

int battle(Player &player,Mob &mob){
	std::string options[4] = {
			"Attack",
			"Defend",
			"Wait",
			"Item"
	};
	unsigned int option = 0;
	unsigned int mob_opt;
	unsigned int dmg = 0;
	while(player.is_alive() && mob.is_alive()) {

		for (unsigned char i = 0; i < 4; i++) {
			std::cout << (int) i + 1 << " " << options[i] << std::endl;
		}

		while (option < 1 || option > 3)
			proper_input(option);

		mob_opt = xorshift128(0, 3);

		if(option == 1) {
			dmg = player.attack(mob);
			std::cout << player.get_name() << "did " << dmg << "damage!" << std::endl;
		}
		if(mob_opt == 0) {
			dmg = mob.attack(player);
			std::cout << mob.get_name() << "did " << dmg << "damage!" << std::endl;
		}
		option = 0;
	}
	if(player.is_alive())
		std::cout << player.get_name() << " defeated " << mob.get_name() << std::endl;
	else
		std::cout << player.get_name() << " was defeated by " << mob.get_name() << std::endl;
	return 0;
}
#endif //ITP298_CAPSTONE_BATTLE_HXX
