/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/30/21.
*
*/

#ifndef ITP298_CAPSTONE_MAIN_HXX
#define ITP298_CAPSTONE_MAIN_HXX
#include <iostream>
#include <string>
#include "terminal.hxx"
#include "includes.hxx"

#include "classes/items/weapon.hxx"
#include "classes/items/armor.hxx"
#include "classes/items/potion.hxx"
#include "classes/fighters/mob.hxx"
#include "data/maps.hxx"
#include "data/mobs.hxx"
#include "data/items.hxx"
#include "data/shops.hxx"
#include "classes/fighters/player.hxx"

#include "menus/map_movement.hxx"
#include "menus/inputs.hxx"
#include "menus/battle.hxx"
#include "menus/shop.hxx"
#include "menus/inventory_menu.hxx"
#include "menus/tutorial_menu.hxx"
/**
 * Saves the players game data
 * @param player
 */
void save_game(const Player &player){
	//start with string stream
	std::stringstream ss;
	//the save file we're going to be writing to
	std::ofstream save_file(player.get_name()+"_save_file.dat");
	//first we get their name, the xp, gold, hp, base hp, base str, base def
	ss << player.name_ << ',' << player.lvl_ << ',' << player.xp_ << ',' << player.gold_ << ',' << player.hp_
	   << ',' << player.bonus_hp_ << ',' << player.bonus_str_ << ',' << player.bonus_def_ << ',' << player.current_game_level;
	//then we get their inventory it is delmited by a [ to seperate it from the other part of the save file
	ss << ",[";

	//the first entry is the number of entries we're dealing with
	ss << player.player_inventory.inventory_quantity() <<',';
	//if they have mroe than 0 items we iterate over their items
	if(player.player_inventory.inventory_quantity() != 0) {
		std::deque<unsigned short> item_ids = player.player_inventory.get_item_ids();
		//then add all of the items based upon their id
		for (unsigned int i = 0; i < player.player_inventory.inventory_quantity(); i++) {
			//store a pair with the id and the amount
			ss << item_ids[i];
			ss << ';' << player.player_inventory.get_quantity(item_ids[i]);
			if (i < (player.player_inventory.inventory_quantity() - 1))
				ss << ',';
		}
	}
	//close this section
	ss << "]";
	save_file << ss.str();
	//store a hash to make sure it's not broke
	save_file << ":" <<std::hex << gen_hash(ss.str());
}
/**
 * Secret function add items to a player from the token string. Eventually this'd be a class but I ran out of time.
 *
 * @param p The player object
 * @param item_tokens the token string representing their inventory
 */
void __add_items(Player &p, const std::string& item_tokens){
	size_t split = 0;
	size_t tok_start = 0;
	split = item_tokens.find(',');
	//find the number of items
	unsigned short num_items = std::stoul(item_tokens.substr(0,split));
	if(num_items == 0)
		return;
	unsigned int idx;
	unsigned short item_id;
	unsigned short item_number;
	std::string item_tuple;
	tok_start = split+1;
	split = item_tokens.find(',',split+1);
	//now iterate over it adding items.
	while(tok_start != std::string::npos){
		item_tuple = item_tokens.substr(tok_start,split-tok_start);
		idx = item_tuple.find(';');
		item_id = std::stoul(item_tuple.substr(0,idx));
		item_number = std::stoul(item_tuple.substr(idx+1));
		p.add_item(*ALL_ITEMS_[item_id], item_number);
		tok_start = split;
		split = item_tokens.find(',',split+1);
	}
}

/**
 * Load the player's game
 * @param save_file_name The file name that stores it.
 * @return A freshly created player object with all of their data.
 */
Player load_game(const std::string &save_file_name){
	std::ifstream save_file(save_file_name);
	//make sure we can read the file.
	if(!save_file.is_open()){
		std::cerr << "\x1b[" << BRIGHT_RED_TXT << "mFile doesn't exist" << "\x1b[0m";
		exit(1);
	}
	else if(save_file.fail()){
		std::cerr << "\x1b[" << BRIGHT_RED_TXT << "mFile can't be read\x1b[0m";
		exit(2);
	}
	//now we start
	std::string save_string;
	std::string token;
	save_file >> save_string;
	size_t split = save_string.find(':')+1;
	//check the hash
	unsigned long ck_hash = std::stoul(save_string.substr(split),nullptr,16);
	unsigned long hash = gen_hash(save_string.substr(0,split-1));
	//bail
	if(ck_hash != hash){
		std::cerr << "Invalid checksum. Save file is corrupted. Can't load from this file!\n";
		exit(1);
	}
	std::string player_name;
	unsigned int xp=0;
	unsigned int gold=0;
	unsigned long hp=0;
	unsigned short lvl=0;
	unsigned short current_game_level=0;
	double bonus_hp=0.00;
	double bonus_str=0.00;
	double bonus_def=0.00;

	//really really ugly code below.
	size_t tok_start = 0;
	split = save_string.find(',');
	unsigned int current_idx = 0;
	//iterate over all of the options till we get all of the values we need.
	while(split != std::string::npos){
		token = save_string.substr(tok_start,split-tok_start);
		switch(current_idx){
			case 0:
				player_name = token;
				break;
			case 1:
				//lvl
				lvl = std::stoul(token);
				break;
			case 2:
				//xp
				xp = std::stoul(token);
				break;
			case 3:
				//gold
				gold = std::stoul(token);
				break;
			case 4:
				//hp
				hp = std::stoul(token);
				break;
			case 5:
				//bonus hp
				bonus_hp = std::stod(token);
				break;
			case 6:
				//bonus_str
				bonus_str = std::stod(token);
				break;
			case 7:
				//bonus_def
				bonus_def = std::stod(token);
				break;
			case 8:
				//current_game_level
				current_game_level = std::stoul(token);
				break;
			default:
				//should never get here.
				break;
		}
		//increment the index
		current_idx++;
		//set the new start
		tok_start = split+1;
		//find next token substring
		split = save_string.find(',',split+1);
		//we're done with the normal items.
		if(current_idx == 9)
			break;
	}
	//somehow we broke out early
	if(current_idx != 9){
		std::cerr << "\x1b[" << BRIGHT_RED_TXT << "mSOMETHING IS BROKEN JIM!\x1b[0m" << std::endl;
		exit(1);
	}
	//get the string minus the hash
	split = save_string.find(':');
	Player p(player_name, lvl,bonus_hp,bonus_str,bonus_def,xp,gold,current_game_level);
	if(p.get_hp() > hp){
		p.damage((hp-p.get_hp())+p.get_def());
	}
	//get the item token substring
	token = save_string.substr(tok_start+1,split-tok_start-2);
	//add the items
	__add_items(p,token);
	//return teh player object
	return p;
}

/**
 * Redrwas the main menu for now. Will eventually be a Menu object.
 */
void redraw_main(){
	std::cout << "\x1b[" << BRIGHT_WHITE_TXT << ";" << BLACK_BG << "m";
	std::string padding_string(53,' ');

	std::cout << "Welcome to the world of Dangling Pointers, where adventure awaits!\n\n\n";
	//draw text-box
	std::cout << "+------------------------------------------------------+"
			  << "\n| 1) Start a new Game 2) Load a saved game" << padding_string.substr(0,13) << "|\n"
			  << "| 3) Exit the game" << padding_string.substr(0,37) << "|\n"
			  << "|                                                      |\n"
			  << "+------------------------------------------------------+" << std::endl;
}
//this code isn't ready as C++ isn't. So commented out for now.
//std::string select_save_file(){
//	std::string path = ".";
//	std::string tmp_filename;
//	clear_textbox(7,3);
//	move_cursor(11,1);
//	unsigned short options = 0;
//	for(const auto &entry: std::filesystem::directory_iterator(path)){
//		if(entry.is_regular_file()) {
//			tmp_filename = entry.path().filename();
//			if (tmp_filename.find("save_file.dat") != std::string::npos) {
//				std::cout << tmp_filename << std::endl;
//			}
//		}
//	}
//}
#endif //ITP298_CAPSTONE_MAIN_HXX
