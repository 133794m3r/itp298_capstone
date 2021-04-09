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

void show_battle_message(const std::string &message){
	std::string new_str = message;
	//the padding string we'll use to pad all inputs until the end.
	std::string padding_string(53, ' ');
	move_cursor(8,3);
	size_t message_len = message.size();
	if(message_len < 55){
		std::cout << new_str << padding_string.substr(0,53-message_len);
		move_cursor(9,3);
		std::cout << padding_string;
	}
	else {
		text_wrap(new_str, 53);
		size_t new_line = new_str.find('\n');
		std::cout << new_str.substr(0,new_line) << padding_string.substr(0,53-new_line);
		move_cursor(9,3);
		std::cout << new_str.substr(new_line+1) << padding_string.substr(0,53-(message_len - new_line));
	}
	move_cursor(11,1);
	clear_line(11);
}

int battle(Player &player,Mob &mob){
	clear_and_move_top();
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

	std::cout << "Lvl XXX " << mob.get_name() << std::endl;
	std::cout << "YYY/ZZZZ" << std::endl << std::endl;
	 //printf("%56s",player.get_name().c_str());
 	std::cout << std::right << std::setw(56) << "Lvl 255 " + player.get_name() << std::endl;
 	std::cout << std::setw(56) <<
	 " " + std::to_string(200) + "/" + std::to_string(1255)
	 << std::endl << std::endl;


 	std::string menu_string; //the menu string that's going to contain our options
	//the message that we're going to send.
	std::string message;
	std::string padding_string(54, ' ');

 	std::cout << "+------------------------------------------------------+"
	 << std::endl << "|" << padding_string << "|" << std::endl
 	 << "|" << padding_string << "|"
 	 << std::endl << "+------------------------------------------------------+" << std::endl;

	for(unsigned int i=1;i<=options.size();i++){
		menu_string += std::to_string(i) + ")" + options[i-1];
	}


	move_cursor(8,2);
	//print_wrap(menu_string,54);
	show_battle_message(menu_string);
	move_cursor(11,1);
	std::cout << "\x1b[" << BOLD << "mSelection\x1b[" << UN_BOLD << "m: ";

	// we only continue the battle as long as both participants are alive
	while(player.is_alive() && mob.is_alive()) {
		option = valid_option(1,options.size());
		//have the mob randomly select one for now.
		mob_opt = xorshift128(0, 3);
		//currently only doing the attack one
		if(option == 1) {
			dmg = player.attack(mob);
			message = player.get_name() + " did " + std::to_string(dmg) + " damage!";
			show_battle_message(message);
			std::cout.flush();
			pause();
		}
		//mobs can attack for now otherwise they do nothing that turn.
		if(mob_opt == 0) {
			dmg = mob.attack(player);
			message = mob.get_name() + " did "  + std::to_string(dmg) + " damage!";
			show_battle_message(message);
			std::cout.flush();
		}
		pause();
		//reset the option to 0.
		option = 0;
		show_battle_message(menu_string);
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
