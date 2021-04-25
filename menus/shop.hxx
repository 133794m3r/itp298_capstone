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
class ShopMenu {
  private:
	ShopKeeper *shop_keeper;
	Player *player;
	unsigned int menu = 0;
	static const std::string padding_string;
	std::string buy_menu_string;
	std::string sell_menu_string;

	std::vector<InventoryMenuTuple> shop_items;
	std::vector<InventoryMenuTuple> player_items;

	void update_buy_menu(){
		for(unsigned int i = 0; i < shop_items.size(); i++){
			buy_menu_string += std::to_string(i + 1) + ")" + shop_items[i].item_name +
							   this->padding_string.substr(0, 14 - shop_items[i].item_name.size()) + ';';
		}
		buy_menu_string +=
				std::to_string(shop_items.size() + 1) + ")Sell Items;    " + std::to_string(shop_items.size() + 2) +
				")Exit Shop   ;";
	}

	void update_shop_text(){
		move_cursor(2,1);
		std::cout << "Shop Inventory\n";
		for(unsigned int i = 0; i < shop_items.size(); i++){
			std::cout << shop_items[i].item_name << " x " <<
					  shop_items[i].item_quantity << ' ' << shop_items[i].item_value <<
					  "g";

			if (i < shop_items.size() - 1)
				std::cout << "; ";
		}
		std::cout << "\n\n\n";
	}

	void update_player_text(){

		std::cout << "\n\n\n";
	}
	void update_sell_menu(){
		for(unsigned short i=0;i<player_items.size();i++){
			sell_menu_string += std::to_string(i+1) + ")" + player_items[i].item_name + this->padding_string.substr(0,14 - player_items[i].item_name.size()) + ';';
		}
		sell_menu_string += std::to_string(player_items.size()+1) + ")Buy Items;     " + std::to_string(shop_items.size() + 2) + ")Exit Shop   ;";
	}

  public:
	ShopMenu(ShopKeeper &shop_keeper, Player &player){
		this->shop_keeper = &shop_keeper;
		this->player = &player;
		shop_keeper.enter_shop(player);
		this->shop_items = shop_keeper.show_inventory();
		this->update_buy_menu();
		this->player_items = player.show_inventory();
	}
	static void show_menu_message(const std::string message) {
		std::string new_str = message;
		//the padding string we'll use to pad all inputs until the end.
		std::string padding_string(53, ' ');
		move_cursor(7, 3);
		size_t message_len = message.size();
		if (message_len < 55) {
			std::replace(new_str.begin(), new_str.end(), ';', ' ');
			std::cout << new_str << padding_string.substr(0, 54 - message_len);
			move_cursor(8, 3);
			std::cout << padding_string;
		}
		else {
			text_wrap(new_str, 53, ';');
			std::replace(new_str.begin(), new_str.end(), ';', ' ');
			size_t new_line = new_str.find('\n');
			std::cout << new_str.substr(0, new_line - 1) << padding_string.substr(0, 53 - new_line);
			move_cursor(8, 3);
			size_t line_2 = new_str.find('\n', new_line + 1);
			if (line_2 != std::string::npos) {
				std::cout << new_str.substr(new_line + 1, line_2 - (new_line + 1))
						  << padding_string.substr(0, 53 - (line_2 - new_line));
				move_cursor(9, 3);
				std::cout << new_str.substr(line_2 + 1) << padding_string.substr(0, 53 - (message_len - line_2));
			}
			else {
				std::cout << new_str.substr(new_line + 1)
						  << padding_string.substr(0, 53 - (message_len - new_line + 1));
			}
		}
		move_cursor(11, 1);
		clear_current_line();
	}

	unsigned short purchase_menu() {
		while(1) {
			std::cout << "\x1b[1mWhat'll it be?\x1b[22m: ";
			unsigned int choice = valid_option(1, this->shop_items.size(), "What'll it be?");
			if (choice < 4) {
				unsigned int amount;
				unsigned int max_amt = std::min(this->player->get_gold() /this-> shop_items[choice].item_value,this->shop_items[choice].item_quantity);
				std::cout << "You can purchase " << max_amt
						  << "\nHow many? ";
				amount = valid_option(0, max_amt);
				if (amount != 0) {
					clear_textbox(7, 3);
					move_cursor(7, 3);
					std::cout << "1) Yes        2) No" << this->padding_string.substr(0, 32);
					clear_lines(11, 3);
					std::cout << "Are you sure you want to buy " << amount << " " << this->shop_items[choice].item_name
							  << " for "
							  <<
							  this->shop_items[choice].item_value * amount << "g?\n\x1b[1mSelection:\x1b[22m";
					max_amt = valid_option(1, 2);
					if (max_amt == 1) {
						bool status = this->shop_keeper->purchase_item(choice, amount);
						clear_textbox(7, 3);
						move_cursor(7, 3);
						if (status) {
							std::cout << this->player->get_name() << " purchased " << amount << this->shop_items[choice].item_name
									  << " for " << this->shop_items[choice].item_value * amount << "g";
							if(this->shop_items[choice].item_quantity == amount) {
								this->update_buy_menu();
								this->update_shop_text();
								this->shop_items.erase(this->shop_items.begin()+choice);
							}
						}
						else {
							std::cout << "You didn't have enough gold or you tried to purchase more than it had!";
						}
						pause();
					}
				}
			}
			else {
				return choice;
			}
		}
	}

	unsigned short sell_menu(){
		return 0;
	}

	void shop_menu() {
		clear_and_move_top();
		std::cout << "Welcome to " << this->shop_keeper->get_name() << "'s shop. What'll you have?" << std::endl;
		this->update_shop_text();

		//draw the text-box.
		std::cout << "+------------------------------------------------------+"
				  << std::endl << "|" << this->padding_string << "|" << '\n'
				  << "|" << this->padding_string << "|" << '\n'
				  << "|" << this->padding_string << "|"
				  << '\n' << "+------------------------------------------------------+" << std::endl;


		show_menu_message(this->buy_menu_string);
		unsigned short cur_choice = 0;

		while(1){
			if(this->menu == 0)
				cur_choice = purchase_menu();
			else
				cur_choice = sell_menu();
			if(cur_choice == 4) {
				//redraw the menu text options.
				if(this->menu)
					this->update_shop_text();
				else
					this->update_player_text();
				//swap the current menu we're on
				this->menu = !this->menu;
			}
			else{
				break;
			}
		}
		return;
	}
	~ShopMenu(){
		this->shop_keeper->exit_shop();
	}
};
const std::string ShopMenu::padding_string = "                                                      ";
#endif //ITP298_CAPSTONE_SHOP_HXX
