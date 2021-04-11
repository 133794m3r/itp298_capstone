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

void redraw_hp(const Actor &actor, bool player=false){
	if(player) {
		//move the cursor to the proper place before outputting.
		move_cursor(5, 1);
		std::cout << std::setw(56) <<
		"HP " + std::to_string(actor.get_hp()) +
		"/" + std::to_string(actor.get_base_hp());
	}
	else {
		//move to proper place
		move_cursor(2, 1);
		//padding is here so that it redraws the whole line.
		std::cout << std::left << std::setw(20) << "HP " + std::to_string(actor.get_hp())
		+ "/" + std::to_string(actor.get_base_hp());
		//reset to default padding mode
		std::cout << std::right;
	}
	//move the cursor back where it belongs
	move_cursor(11,1);
}

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
//might make this whole thing be abstracted away into the Battle class and then have the printing and such be done via the "complete_turn" method to make testing easier but that's later me's problem.
/**
 * Battle simulator function.
 *
 * @param player The player object we're operating on.
 * @param mob The mob we're currently fighting.
 * @return If the player is still alive after the battle.
 */
bool battle(Player &player,Mob &mob){
	clear_and_move_top();
	std::array<std::string,3> options = {
			"Attack",
			"Defend",
			"Item",
//			"Wait",
//			"Something",
//			"Else",
	};

	for(unsigned char i=0;i<options.size();i++){
		options[i].append(14-options[i].size(),' ');
	}
	//the forward declaration of the options.
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

	//draw the initial UI
	std::cout << "Lvl " << static_cast<int>(mob.get_lvl()) << " " << mob.get_name() << std::endl;
	std::cout << "HP " << mob.get_hp() << "/" << mob.get_base_hp() << std::endl << std::endl;
 	std::cout << std::setw(56) << "Lvl "  + std::to_string(player.get_lvl()) + " " + player.get_name() << std::endl;
	std::cout << std::setw(56) << "HP " + std::to_string(player.get_hp()) + "/" + std::to_string(player.get_base_hp()) << std::endl << std::endl;

 	std::string menu_string; //the menu string that's going to contain our options
	//the message that we're going to send.
	std::string message;
	std::string padding_string(54, ' ');
	//draw the text-box.
 	std::cout << "+------------------------------------------------------+"
	 << std::endl << "|" << padding_string << "|" << std::endl
 	 << "|" << padding_string << "|"
 	 << std::endl << "+------------------------------------------------------+" << std::endl;

 	//generate the menu string
	for(unsigned int i=1;i<=options.size();i++){
		menu_string += std::to_string(i) + ")" + options[i-1];
	}

	//move the cursor to within the text box.
	move_cursor(8,2);
	//display message
	show_battle_message(menu_string);
	//move it back to it's original position
	move_cursor(11,1);
	//show the selection prompt
	std::cout << "\x1b[1mSelection\x1b[22m: ";

	// we only continue the battle as long as both participants are alive
	while(player.is_alive() && mob.is_alive()) {
		option = valid_option(1,options.size());
		//have the mob randomly select one for now.
		mob_opt = xorshift128(0, 3);
		//currently only doing the attack one
		switch(option){
			case 1:
				dmg = player.attack(mob);
				message = player.get_name() + " did " + std::to_string(dmg) + " damage!";
				if(dmg != 0)
					redraw_hp(mob);
				else
					message  = player.get_name() + " missed completely!";

				break;
			case 2:
				message = player.get_name() + " is thinking of their next move.";
				break;
		}
		show_battle_message(message);
		pause();
		//mobs can attack for now otherwise they do nothing that turn.
		//if it's dead time to break out of it as the mob can't act.
		if(!mob.is_alive())
			break;

		//no AI right now really. mob options will be the same as the player for simplicity
		if(mob_opt == 0) {
			dmg = mob.attack(player);
			message = mob.get_name() + " did "  + std::to_string(dmg) + " damage!";

			if(dmg != 0)
				redraw_hp(player,true);
			else
				message = mob.get_name() + " missed completely!";


		}
		else{
			message = mob.get_name() + " stands there and seems to be thinking of something...";
		}
		show_battle_message(message);

		pause();
		//reset the option to 0.
		option = 0;
		show_battle_message(menu_string);
		std::cout << "\x1b[1mSelection\x1b[22m: ";
	}
	//figure out who died
	if(player.is_alive()) {
		std::cout << player.get_name() << " defeated " << mob.get_name() << std::endl;
		return true;
	}
	else {
		std::cout << player.get_name() << " was defeated by " << mob.get_name() << std::endl;
		return false;
	}
}
#endif //ITP298_CAPSTONE_BATTLE_HXX
