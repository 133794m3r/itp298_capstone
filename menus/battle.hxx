/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#ifndef ITP298_CAPSTONE_BATTLE_HXX
#define ITP298_CAPSTONE_BATTLE_HXX
#include <iomanip>
#include "../includes.hxx"
#include "../classes/fighters/player.hxx"
#include "../classes/fighters/mob.hxx"
#include "inputs.hxx"

int battle(Player &player,Mob &mob){
	std::array<std::string,5> options = {
			"Attack",
			"Defend",
			"Item",
			"Wait",
			"Something",
//			"Else",
	};
	for(unsigned char i=0;i<options.size();i++){
		options[i].append(14-options[i].size(),' ');
	}
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
	char hp = 50;
	std::cout << mob.get_name() << std::endl;
	std::cout << "Lvl XX" << "YYY/ZZZZ" << std::endl << std::endl;
	 //printf("%56s",player.get_name().c_str());
 	std::cout << std::right << std::setw(56) << player.get_name() << std::endl;
 	std::cout << std::setw(56) << "Lvl " + std::to_string(hp)
	 + " " + std::to_string(200) + "/" + std::to_string(1255)
	 << std::endl << std::endl;
 	std::cout << "+------------------------------------------------------+"
	 << std::endl << "|";
	for(unsigned int i=1;i<=options.size();i++){
		std::cout << " " << i << ") " << options[i-1];
		if(i > 2 && i % 3 == 0){
			std::cout << "|" <<std::endl;
			if(i < options.size())
				std::cout << "|";
		}
	}
	if(options.size() > 4 && options.size() < 6) {
		unsigned int padding = 54;
		for (unsigned int i = 0; i <= options.size() % 4; i++) {
			padding -= options[options.size() - i - 1].size() + 4;
		}
		std::cout << std::setw(padding) << " " << "|" << std::endl;

	}
	std::cout <<"+------------------------------------------------------+" << std::endl;
	std::cout << "\x1b[" << BOLD << "mSelection\x1b[" << UN_BOLD << "m: ";
	// we only continue the battle as long as both participants are alive
	while(player.is_alive() && mob.is_alive()) {
		option = valid_option(1,options.size());
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
		pause();
		move_and_clear_terminal(5);
		std::cout << "\x1b[1mSelection\x1b[22m: ";
	}
	//figure out who died
	if(player.is_alive())
		std::cout << player.get_name() << " defeated " << mob.get_name() << std::endl;
	else
		std::cout << player.get_name() << " was defeated by " << mob.get_name() << std::endl;
	return 0;
}
#endif //ITP298_CAPSTONE_BATTLE_HXX
