/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#ifndef ITP298_CAPSTONE_BATTLE_HXX
#define ITP298_CAPSTONE_BATTLE_HXX
//global C++ specific stuff
#include <iomanip>
//solely for MSVC++ compiler as for some reason it doesn't include C++ in it's standard templates(for reasons) during compilation.
#include <array>
#include <algorithm>
//Local includes
#include "../includes.hxx"
#include "../classes/fighters/player.hxx"
#include "../classes/fighters/mob.hxx"
#include "inputs.hxx"

void redraw_hp(const Actor &actor){
	if(actor.get_id() == 65535) {
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
		std::replace(new_str.begin(),new_str.end(),';',' ');
		std::cout << new_str << padding_string.substr(0,53-message_len);
		move_cursor(9,3);
		std::cout << padding_string;
	}
	else {
		text_wrap(new_str, 53,';');
		std::replace(new_str.begin(),new_str.end(),';',' ');
		size_t new_line = new_str.find('\n');
		std::cout << new_str.substr(0,new_line) << padding_string.substr(0,53-new_line);
		if(new_line != std::string::npos) {
			move_cursor(9, 3);
			std::cout << new_str.substr(new_line + 1) << padding_string.substr(0, 53 - (message_len - new_line));
		}
	}
	move_cursor(11,1);
	clear_current_line();
}

std::string update_potions(std::vector< std::pair<menu_item_data, unsigned short> > &potions, Player &player){
	potions = player.get_potions();
	std::string potions_opt;
	if(!potions.empty()) {
		unsigned int max = std::min(potions.size(), static_cast<unsigned long>(4));
		for (unsigned int i = 0; i < max; i++) {

			potions_opt +=
					std::to_string(i+1) + ")" + potions[i].first.item_name + "x" + std::to_string(potions[i].first.item_quantity) +
					';';
		}
		potions_opt += std::to_string(potions.size()+1)+")Exit   ;";
	}
	return potions_opt;
}

//might make this whole thing be abstracted away into the Battle class and then have the printing and such be done via the "complete_turn" method to make testing easier but that's later me's problem.
/**
 * Battle simulator function.
 *
 * @param player The player object we're operating on.
 * @param mob The mob we're currently fighting. It's copied to the function so that we can reuse later.
 * @return If the player is still alive after the battle.
 */
bool battle(Player &player,Mob mob){
	clear_and_move_top();
	std::array<std::string,3> options = {
			"Attack",
			"Defend",
			"Item",
//			"Wait",
//			"Something",
//			"Else",
	};

	for(auto & option : options){
		option.append(14-option.size(),' ');
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

	switch(mob.get_tier()){
		case 0:
			//gray/trash
			std::cout << "\x1b[90m";
			break;
		case 2:
			//green/rare
			std::cout << "\x1b[1;92m";
			break;
		case 3:
			//blue/elite
			std::cout << "\x1b[1;94m";
			break;
		case 4:
			//purple rare elite
			std::cout << "\x1b[1;95mElite ";
			break;
		case 5:
			//yellow mini boss
			std::cout << "\x1b[1;93m";
			break;
		case 6:
			//red boss
			std::cout << "\x1b[1;91mBoss ";
			break;
		default:
			break;
	}

	std::cout <<  mob.get_name() << "\x1b[97;22m";
	std::cout << " Lvl: ";
	if(mob.get_tier() > 4)
		std::cout << "???";
	else
		std::cout << mob.get_lvl();

	std::cout << '\n';
	std::cout << "HP " << mob.get_hp() << "/" << mob.get_base_hp() << "\n\n";
 	std::cout << std::setw(56) << "Lvl "  + std::to_string(player.get_lvl()) + " " + player.get_name() << '\n';
	std::cout << std::setw(56) << "HP " + std::to_string(player.get_hp()) + "/" + std::to_string(player.get_base_hp()) << "\n\n";

 	std::string menu_string; //the menu string that's going to contain our options
	//the message that we're going to send.
	std::string message;
	std::string padding_string(54, ' ');
	//draw the text-box.
 	std::cout << "+------------------------------------------------------+\n|" << padding_string << "|\n"
 	 << "|" << padding_string << "|\n+------------------------------------------------------+" << std::endl;

 	//generate the menu string
	for(unsigned int i=1;i<=options.size();i++){
		menu_string += std::to_string(i) + ")" + options[i-1] + ';';
	}

	//move the cursor to within the text box.
	move_cursor(8,2);
	//display message
	show_battle_message(menu_string);
	//move it back to it's original position
	move_cursor(11,1);
	//show the selection prompt
	std::cout << "\x1b[1mSelection\x1b[22m: ";
	std::string potions_opt;
	std::vector<std::pair<menu_item_data, unsigned short >> potions;
	potions_opt = update_potions(potions,player);
	// we only continue the battle as long as both participants are alive
	while(player.is_alive() && mob.is_alive()) {
		option = valid_option(1,options.size());
		//have the mob randomly select one for now.
		mob_opt = xorshift128(static_cast<unsigned int>(0), static_cast<unsigned int>(3));
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
			//the only other option is 3.
			case 3:
				//see if they have any potions to use.
				if(potions.size() != 0){
					//if their HP is at max don't let them use one.
					if(player.get_hp() == player.get_base_hp()){
						message = "Using a potion now wouldn't do any good!";
					}
					//otherwise let them try to use one.
					else{
						//set the default message unless they do something else.
						message = player.get_name() + " decided to wait this turn out!";

						//show the options and their counts.
						show_battle_message(potions_opt);
						//show the prompt
						std::cout << "\x1b[1mSelection\x1b[22m: ";
						option = valid_option(1,potions.size()+1);
						//they want to use a potion
						if(option <= potions.size()){
							//make sure they want to use that potion
							show_battle_message("Do you want to use " + potions[option-1].first.item_name + "; to heal " + std::to_string(potions[option-1].first.item_value) + "hp?;1)Yes     2)No    ");
							std::cout << "\x1b[1mSelection\x1b[22m: ";
							option = valid_option(1,2);
							//they do.
							if(option == 1){
								//add this much hp
								unsigned short added = player.add_hp(potions[option-1].first.item_value);
								//remove it from their inventory
								player.remove_item(potions[option-1].second);
								//redraw the hp UI
								redraw_hp(player);
								//update the potions string/message.
								potions_opt = update_potions(potions,player);
								//say how much HP they healed
								message = "You healed " + std::to_string(added) +" HP!";
							}
						}
					}
				}
				else{
					//can't use what you don't have
					message = player.get_name() + " doesn't have any potions!";
				}
		}
		//show the message from their turn.
		show_battle_message(message);
		//pause for a turn.
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
				redraw_hp(player);
			else
				message = mob.get_name() + " missed completely!";

		}
		else{
			//message is weird due to my not so good text-wrapper function.
			message = mob.get_name() + " stands; there and seems to ;be thinking of ;something;...";
		}
		//show the mob's turn stuff
		show_battle_message(message);
		//make sure to flush out the cout buffer
		std::cout.flush();
		//pause again
		pause();
		//reset message
		message = "";
		//show the menu again
		show_battle_message(menu_string);
		std::cout << "\x1b[1mSelection\x1b[22m: ";
	}

	//figure out who died
	if(player.is_alive()) {
		//player won so get the stuff
		std::cout << player.get_name() << " defeated " << mob.get_name() << std::endl;
		MobRewards rewards = mob.rewards();
		std::cout << "You received " << rewards.xp << "xp and " << rewards.gold << "g for defeating the enemy!\n";
		//add xp/gold
		bool lvl_up = player.add_xp(rewards.xp);
		player.add_gold(rewards.gold);
		//if they got any items add those too and tell them.
		if(!rewards.items.empty()){
			std::cout << "And ";
			for(auto item_slot:rewards.items){
				std::cout << " " << item_slot.second << " ";
				switch(item_slot.first->get_tier()){
					case 0:
						std::cout << "\x1b[" << GRAY_TXT << 'm';
						break;
					case 1:
						std::cout << "\x1b[" << BRIGHT_WHITE_TXT << 'm';
						break;
					case 2:
						std::cout << "\x1b[" << BRIGHT_BLUE_TXT << 'm';
						break;
					case 3:
						std::cout << "\x1b[" << BRIGHT_MAGENTA_TXT << 'm';
						break;
					case 4:
						std::cout << "\x1b[" << BRIGHT_YELLOW_TXT << 'm';
						break;
					default:
						std::cout << "\x1b[" << BRIGHT_WHITE_TXT << 'm';
						break;
				}
				std::cout << item_slot.first->get_name() << "\x1b[97m(s) ";
				player.add_item(*item_slot.first,item_slot.second);
			}
			std::cout << "!" << std::endl;
		}
		//otherwise tell them there was no items
		else{
			std::cout << "No items were found near the scene!" << std::endl;
		}
		//pause again to show them it
		pause();
		if(lvl_up){
			std::cout << "You leveled up! You feel stronger now!\n";
		}
		//they lived
		return true;
	}
	else {
		//say that they died.
		std::cout << player.get_name() << " was defeated by " << mob.get_name() << std::endl;
		pause();
		//they died
		return false;
	}
}
#endif //ITP298_CAPSTONE_BATTLE_HXX
