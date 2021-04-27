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
	//have a copy of the shop keeper
	ShopKeeper *shop_keeper;
	//same with player
	Player *player;
	//some basic properties
	unsigned int menu = 0;
	static const std::string padding_string;
	std::string buy_menu_string;
	std::string sell_menu_string;

	std::vector<InventoryMenuTuple> shop_items;
	std::vector<InventoryMenuTuple> player_items;

	/**
	 * Updates the buy strings menu
	 */
	void update_buy_menu(){
		this->buy_menu_string = "";
		for(unsigned int i = 0; i < this->shop_items.size(); i++){
			this->buy_menu_string += std::to_string(i + 1) + ")" + this->shop_items[i].item_name +
							   this->padding_string.substr(0, 14 - this->shop_items[i].item_name.size()) + ';';
		}
		this->buy_menu_string +=
				std::to_string(this->shop_items.size() + 1) + ")Sell Items    ;" + std::to_string(this->shop_items.size() + 2) +
				")Exit Shop   ;";
	}

	//updates the shop text for when you're buying items
	void update_shop_text(){
		move_cursor(2,1);
		clear_lines(2,2);
		std::cout << "Shop Inventory";
		move_cursor(2,30);
		std::cout << "Current Money:" << this->player->get_gold() << "g\n";
		for(unsigned int i = 0; i < this->shop_items.size(); i++){
			std::cout << this->shop_items[i].item_name << " x " <<
					  this->shop_items[i].item_quantity << ' ' << this->shop_items[i].item_value <<
					  "g";

			if (i < this->shop_items.size() - 1)
				std::cout << "; ";
		}
		std::cout << "\n\nPurchase Options\n";
	}

	//update the selling text screen
	void update_player_text(){
		move_cursor(2,1);
		clear_lines(2,2);
		std::cout << this->player->get_name() << "'s Inventory";
		move_cursor(2,30);
		std::cout << "Current Money:"  <<  this->player->get_gold() << "g\n";
		for(unsigned int i = 0; i < this->player_items.size(); i++){
			std::cout << this->player_items[i].item_name << " x " <<
					  this->player_items[i].item_quantity << ' ' << this->player_items[i].item_value <<
					  "g";

			if (i < this->player_items.size() - 1)
				std::cout << "; ";
		}
		std::cout << "\n\nSell Options    \n";
	}

	//updates the items to be sold menu.
	void update_sell_menu(){
		this->sell_menu_string = "";
		for(unsigned short i=0;i<this->player_items.size();i++){
			this->sell_menu_string += std::to_string(i+1) + ")" + this->player_items[i].item_name +
					this->padding_string.substr(0,14 - this->player_items[i].item_name.size()) + ';';
		}
		this->sell_menu_string += std::to_string(player_items.size()+1) + ")Buy Items;     " +
				std::to_string(this->player_items.size() + 2) + ")Exit Shop   ;";
	}

	//still not done yet
	void update_shop_items(){

	}
	//ditto here
	void update_player_items(){

	}
  public:
	//constructor
	ShopMenu(ShopKeeper &shop_keeper, Player &player){
		this->shop_keeper = &shop_keeper;
		this->player = &player;
		shop_keeper.enter_shop(player);
		this->shop_items = shop_keeper.show_inventory();
		this->update_buy_menu();
		this->player_items = player.show_inventory();
		this->update_sell_menu();
	}

	/**
	 * Static method to print the strings in the text-box.
	 * Make make this part of the base Menu class once I get to it.
	 *
	 * @param message The message to be displayed.
	 */
	static void show_menu_message(const std::string message) {
		std::string new_str = message;
		//the padding string we'll use to pad all inputs until the end.
		std::string padding(53, ' ');
		move_cursor(7, 3);
		size_t message_len = message.size();
		//lots of complex text-wrapping ensues.
		if (message_len < 55) {
			std::replace(new_str.begin(), new_str.end(), ';', ' ');
			std::cout << new_str << padding.substr(0, 53 - message_len);
			move_cursor(8, 3);
			std::cout << padding;
		}
		else {
			text_wrap(new_str, 53, ';');
			std::replace(new_str.begin(), new_str.end(), ';', ' ');
			size_t new_line = new_str.find('\n');
			std::cout << new_str.substr(0, new_line - 1) << padding.substr(0, 53 - new_line);
			move_cursor(8, 3);
			size_t line_2 = new_str.find('\n', new_line + 1);
			if (line_2 != std::string::npos) {
				std::cout << new_str.substr(new_line + 1, line_2 - (new_line + 1))
						  << padding.substr(0, 53 - (line_2 - new_line));
				move_cursor(9, 3);
				std::cout << new_str.substr(line_2 + 1) << padding.substr(0, 53 - (message_len - line_2));
			}
			else {
				std::cout << new_str.substr(new_line + 1)
						  << padding.substr(0, 53 - (message_len - new_line + 1));
			}
		}
		move_cursor(11, 1);
		clear_current_line();
	}

	/**
	 * The menu portiont o be shown when buying items.
	 * @return The choice(1-2) saying if we're switching menus or leaving the shop
	 */
	unsigned short purchase_menu() {
		//show the menu string
		show_menu_message(this->buy_menu_string);
		//infinite loop
		while(1) {
			//show prefix
			std::cout << "\x1b[1mWhat'll it be?\x1b[22m: ";
			unsigned int choice = valid_option(1, this->shop_items.size()+2, "What'll it be?");
			//see if it's an item they chose
			if(choice <= this->shop_items.size()){
				unsigned int amount;
				//decrease by 1
				choice--;
				//move terminal
				move_and_clear_terminal(1);
				//figure out max they can buy
				unsigned int max_amt = std::min(this->player->get_gold() /this->shop_items[choice].item_value,this->shop_items[choice].item_quantity);
				std::cout << "You can purchase " << max_amt << " " << this->shop_items[choice].item_name << "(s)\nHow many? ";
				//make sure they don't try to get more than that.
				amount = valid_option(0, max_amt);
				//if it's 0 then they didn't meant to try to buy any.
				if (amount != 0) {
					clear_textbox(7, 3);
					move_cursor(7, 3);
					//menu options
					std::cout << "1) Yes        2) No" << this->padding_string.substr(0, 32);
					move_and_clear_down(11);
					//telling info
					std::cout << "Are you sure you want to buy " << amount << " " << this->shop_items[choice].item_name
							  << " for "
							  <<
							  this->shop_items[choice].item_value * amount << "g?\n\x1b[1mSelection:\x1b[22m";
					//check for validity
					max_amt = valid_option(1, 2);
					//they did want to buy it
					if (max_amt == 1) {
						//see if they can
						bool status = this->shop_keeper->purchase_item(choice, amount);
						clear_textbox(7, 3);
						move_cursor(7, 3);
						//they can
						if (status){
							std::cout << this->player->get_name() << " purchased " << amount << " " << this->shop_items[choice].item_name
									  << " for " << this->shop_items[choice].item_value * amount << "g";
							pause();
							this->player_items = this->player->show_inventory();
							this->update_sell_menu();
							if(this->shop_items[choice].item_quantity == amount) {
								this->shop_items.erase(this->shop_items.begin()+choice);
								this->update_buy_menu();
								this->update_shop_text();
								show_menu_message(this->buy_menu_string);
							}
						}
						else {
							//they can't
							std::cout << "You didn't have enough gold or you tried to purchase more than it had!";
							move_cursor(11,1);
							pause();
						}
//						pause();
					}
				}
			}
			//exit loop
			else {
				return choice - this->shop_items.size();
			}
		}
	}

	/**
	 * This is the menu when they're selling their own things.
	 * @return
	 */
	unsigned short sell_menu() {
		//show the player side of things
		this->update_player_text();
		show_menu_message(this->sell_menu_string);
		//all of this code is similar to above but using other properties
		while (1) {
			std::cout << "\x1b[1mSelection\x1b[22m:";
			unsigned int choice = valid_option(1,this->player_items.size() + 2,"Selection");
			if (choice <= this->player_items.size()) {
				choice--;
				std::cout << "You can sell " << this->player_items[choice].item_quantity << "\nHow many?";
				unsigned int amount = valid_option(0, this->player_items[choice].item_quantity);
				if (amount != 0) {
					clear_textbox(7, 3);
					move_cursor(7, 3);
					std::cout << "1) Yes        2) No" << this->padding_string.substr(0, 32);
					clear_lines(11, 3);
					std::cout << "Are you sure you want to sell " << amount << " "
						<< this->player_items[choice].item_name << " for " <<
						std::lround(this->player_items[choice].item_value * amount * 0.75)
						<< "g?\n\x1b[1mSelection:\x1b[22m";

					if(valid_option(1,2) == 1){
						bool status = this->shop_keeper->sell_item(choice, amount);
						clear_textbox(7, 3);
						move_cursor(7, 3);
						if (status) {
							std::cout << this->player->get_name() << " sold " << amount
									  << this->player_items[choice].item_name << " for " <<
									  std::lround(this->player_items[choice].item_value * amount *0.75) << "g";

							if (this->player_items[choice].item_quantity == amount) {
								this->update_sell_menu();
								this->update_player_text();
								this->player_items.erase(this->player_items.begin() + choice);
								show_menu_message(this->sell_menu_string);
							}
						}
						else {
							std::cout << "You didn't have enough items to sell!";
						}
						pause();
					}
				}
				else{
					move_and_clear_down(11);
				}
			}
			else{
				return choice - this->player_items.size();
			}
		}
	}
	/**
	 * The main menu method.
	 */
	void shop_menu() {
		//clear the whole screen
		clear_and_move_top();
		std::cout << "Welcome to " << this->shop_keeper->get_name() << "'s shop. What'll you have?" << std::endl;
		//show initial text
		this->update_shop_text();

		//draw the text-box.
		std::cout << "+------------------------------------------------------+"
				  << std::endl << "|" << this->padding_string << "|" << '\n'
				  << "|" << this->padding_string << "|" << '\n'
				  << "|" << this->padding_string << "|"
				  << '\n' << "+------------------------------------------------------+" << std::endl;



		unsigned short cur_choice = 0;
		//infinite loop
		while(1){
			if(this->menu == 0)
				cur_choice = purchase_menu();
			else
				cur_choice = sell_menu();

			if(cur_choice == 1) {
				//redraw the menu text options.
				if(this->menu)
					this->update_shop_text();
				else
					this->update_player_text();
				//swap the current menu we're on
				this->menu = !this->menu;
			}
			//they said to leave it
			else{
				break;
			}
		}
		return;
	}
	//make sure to remove plyer from teh shop
	~ShopMenu(){
		this->shop_keeper->exit_shop();
	}
};
//teh padding string
const std::string ShopMenu::padding_string = "                                                      ";
#endif //ITP298_CAPSTONE_SHOP_HXX
