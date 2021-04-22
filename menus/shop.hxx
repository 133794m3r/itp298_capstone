/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*
*/

#ifndef ITP298_CAPSTONE_SHOP_HXX
#define ITP298_CAPSTONE_SHOP_HXX

#include <algorithm>
#include "../classes/shopkeeper.hxx"
#include "inputs.hxx"
void show_menu_message(const std::string message){
	std::string new_str = message;
	//the padding string we'll use to pad all inputs until the end.
	std::string padding_string(53, ' ');
	move_cursor(7,2);
	size_t message_len = message.size();
	if(message_len < 55){
		std::replace(new_str.begin(), new_str.end(), ';',' ');
		std::cout << new_str << padding_string.substr(0,54-message_len);
		move_cursor(8,3);
		std::cout << padding_string;
	}
	else {
		text_wrap(new_str, 53,';');
		size_t new_line = new_str.find('\n');
		std::cout << new_str.substr(0,new_line) << padding_string.substr(0,53-new_line);
		move_cursor(9,3);
		std::cout << new_str.substr(new_line+1) << padding_string.substr(0,53-(message_len - new_line));
	}
	move_cursor(11,1);
	clear_line(11);
}

void shop_menu(ShopKeeper &shop_keeper, Player &player){
	clear_and_move_top();
	shop_keeper.enter_shop(player);

	std::vector<InventoryMenuTuple> shop_items = shop_keeper.show_inventory();
	std::cout << "Welcome to " << shop_keeper.get_name() << "'s shop. What'll you have?" << std::endl;
	std::cout << "Shop Inventory \n";
	for(unsigned int i=0;i<shop_items.size();i++){
		std::cout  << shop_items[i].item_name << " x " <<
				   shop_items[i].item_quantity << ' ' << shop_items[i].item_value <<
				   "g";

		if(i < shop_items.size()-1)
			std::cout << "; ";
	}
	std::cout << "\n\n\n";
	std::string padding_string(54, ' ');
	//draw the text-box.
	std::cout << "+------------------------------------------------------+"
			  << std::endl << "|" << padding_string << "|" << '\n'
			  << "|" << padding_string << "|" << '\n'
			  << "|" << padding_string << "|"
			  << '\n' << "+------------------------------------------------------+" << std::endl;
	std::string menu_string; //the menu string that's going to contain our options
	for(unsigned int i=0;i<shop_items.size();i++){
		menu_string += " " + std::to_string(i+1) +")" + shop_items[i].item_name + ';' + padding_string.substr(0,14-shop_items[i].item_name.size());
	}
	show_menu_message(menu_string);
	shop_keeper.exit_shop();
	return;
}
#endif //ITP298_CAPSTONE_SHOP_HXX
