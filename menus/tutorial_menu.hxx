/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/28/21.
*
*/

#ifndef ITP298_CAPSTONE_TUTORIAL_MENU_HXX
#define ITP298_CAPSTONE_TUTORIAL_MENU_HXX
#include "menu.hxx"
class TutorialMenu: public Menu {
  private:
	//basic private properties
	Player *player_;
	//player's inventory
	InventoryMenu *inv_menu;
	//menu string
	std::string menu_string;

	//redraw the whole menu when returning from another menu/first entering this one.
	void redraw_menu(){
		clear_and_move_top();
		std::cout << "Level: Tutorial " << this->player_->get_name() << "'s journey\n";
		this->redraw_stats();
		std::cout << "+------------------------------------------------------+\n|                                                      |\n|                                                      |\n+------------------------------------------------------+" << std::endl;
	}
	//redraw the status bar with basic info about the player.
	void redraw_stats(){
		move_cursor(2,1);
		std::cout << "HP:\x1b[1m" << this->player_->get_hp() << "\x1b[22m/" << this->player_->get_base_hp() << "  Gold:" << this->player_->get_gold() << " XP:" << this->player_->get_xp() << "\n\n";
	}

  public:
	//constructors
	//also initializes base class properties.
	TutorialMenu(Player &player, InventoryMenu &inv):Menu(5,4){
		//make sure they give us a player, their inventory.
		this->player_ = &player;
		this->menu_string = "";
		this->inv_menu = &inv;
	};

	//enter the tutorial
	void enter(){

		//basic setup stuff.
		ShopKeeper tut_shop("Buy something", {&stick, &shirt, &basic_potion}, {1, 1, 10});
		//create shop menu
		ShopMenu tut_shop_menu(tut_shop);
		//tell them some basic stuff
		clear_and_move_top();
		std::cout << "Welcome to the tutorial " << this->player_->get_name() << ".\n";
		print_wrap("To start off with you need to purchase a weapon and armor from the shop. It's also recommended that you purchase some Potions (always end in Pot) to heal yourself during battle and after them. Then you need to equip your new items by entering your inventory. After that you can start the real game.\n",75,false);
		//pause
		pause();
		//draw menu
		this->redraw_menu();
		std::string end_string = "2)Inventory Menu ;3)Continue On ;4)Save Game   ;";
		std::cout << "Level: Tutorial " << this->player_->get_name() << "'s journey\n";
		this->redraw_stats();
		std::cout << "+------------------------------------------------------+\n|                                                      |\n|                                                      |\n+------------------------------------------------------+" << std::endl;
		this->menu_string = "1)Enter Shop;2)Inventory Menu ;3)Continue On  ;4)Save Game    ;";
		/*
		 * 0 = hasn't bought anything. 1 = bought an item and has equipped it, 2 = fought the first rat,
		 * 3 = second rat defeated , 4 = third rat defeated , 5 = shop to buy some potions, 6 = rate king area, 7 =  fought rat king
		 */
		unsigned short tut_status = 0;
		bool player_alive = true;
		//hard coded menu options here due to the player having to continue on.
		while(true) {
			//show menu
			this->show_menu_message(this->menu_string);
			std::cout << "\x1b[1mSelection\x1b[22m: ";
			//prompt for result
			unsigned int choice = valid_option(1, 4);

			switch(choice) {
				case 1:
					if(tut_status <= 1 || tut_status == 5){
						tut_shop_menu.enter_shop(*this->player_);
						tut_shop_menu.shop_menu();
						this->redraw_menu();
					}
					else if(tut_status >= 2 && tut_status <= 4){
						player_alive = battle(*this->player_, rat);

						tut_status++;
						this->redraw_menu();
						if(tut_status == 5){
							this->menu_string = "1)Enter Shop;"+end_string;
							print_wrap("You sense a dark presence before you. It seems extremely powerful. Now seems like a good time to stock up on some Potions.\n",55);
							pause();
							move_and_clear_up(2);
						}
					}
					else{
						player_alive = battle(*this->player_, rat_king);
						tut_status++;
					}
					break;
				case 2:
					inv_menu->enter();
					this->redraw_menu();
					break;
				case 3:
					if(tut_status <= 1){
						if (player_->equipped_armor() != nullptr || player_->equipped_armor() != nullptr) {
							player_alive = battle(*this->player_, rat);
							this->menu_string = "1)Explore the Darkness;"+end_string;
							tut_status = 2;
							clear_and_move_top();
							this->redraw_menu();
						}
						else{
							this->show_menu_message("You sense an extremely dark presence on the horizon. It's best to gear up before moving on.",' ');
							pause();
						}
					}
					else if(tut_status == 4){
						this->menu_string = "1)Enter Shop;" + end_string;
						tut_status++;
					}
					else if(tut_status == 5){
						this->menu_string = "1)Fight Giant Rat;" + end_string;
						tut_status++;
					}
					break;
				case 4:
					std::cout << "Not Yet implemented\n";
					pause();
					break;
				default:
					std::cout << "What did you do?! EMAIL ME IMMEDIATELY THIS SHOULDN'T BE POSSIBLE WITH THE MSG 'WTF I BROKEDED TUTORIAL'!\nadmin-contact@transcendental.us";
					pause();
					break;
			}
			//if the player is dead or we're at the end of the tutorial break out fo the loop.
			if(!player_alive || tut_status == 7) {
				break;
			}
		}
		clear_and_move_top();

		std::cout << "You've completed the tutorial!\n";
		pause();
	}
};


#endif //ITP298_CAPSTONE_TUTORIAL_MENU_HXX

