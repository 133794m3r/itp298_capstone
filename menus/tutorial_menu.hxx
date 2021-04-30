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
	Player *player_;
	InventoryMenu *inv_menu;
	std::string menu_string;
	void update_menu(){
		this->menu_string = "";

	}
	void redraw_stats(){
		move_cursor(2,1);
		std::cout << "HP:\x1b[1m" << this->player_->get_hp() << "\x1b[22m/" << this->player_->get_base_hp() << "  Gold:" << this->player_->get_gold() << " XP:" << this->player_->get_xp() << "\n\n";
	}
  public:
	TutorialMenu(Player &player, InventoryMenu &inv):Menu(5,4){
		this->player_ = &player;
		this->menu_string = "";
		this->inv_menu = &inv;
	};

	void enter(){
		ShopKeeper tut_shop("Buy something", {&stick, &shirt, &basic_potion}, {1, 1, 10});
		ShopMenu tut_shop_menu(tut_shop);
		std::cout << "Welcome to the tutorial " << this->player_->get_name() << ".\n To start off with you need to purchase a weapon and armor from the shop. It's also recommended that you purchase some Potions(always end in Pot) to heal yourself during battle and after them.\nThen you need to equip your new items by entering your inventory. After that you can start the real game.\n";
		pause();
		move_and_clear(1);
		std::string end_string = "2)Inventory Menu;3)Continue On ;4)Save Game   ;";
		std::cout << "Level: Tutorial " << this->player_->get_name() << "'s journey\n";
		this->redraw_stats();
		std::cout << "+------------------------------------------------------+\n|                                                      |\n|                                                      |\n+------------------------------------------------------+" << std::endl;
		this->menu_string = "1)Enter Shop;2)Inventory Menu;3)Continue On  ;4)Save Game    ;";
		/*
		 * 0 = hasn't bought anything. 1 = bought an item and has equipped it, 2 = fought the first rat,
		 * 3 = second rat defeated , 4 = third rat defeated , 5 = shop to buy some potions, 6 = rate king area, 7 =  fought rat king
		 */
		unsigned short tut_status = 0;
		bool player_alive = true;
		bool killed_mob = false;
		//hard coded menu options here due to the player having to continue on.
		while(true) {
			this->show_menu_message(this->menu_string);
			std::cout << "\x1b[1mSelection\x1b[22m: ";

			unsigned int choice = valid_option(1, 4);

			switch (choice) {
				case 1:
					if(tut_status <= 1 || tut_status == 5){
						tut_shop_menu.enter_shop(*this->player_);
						tut_shop_menu.shop_menu();
					}
					else if(tut_status >= 2 && tut_status <= 4){
						player_alive = battle(*this->player_, rat);
						tut_status++;
					}
					else{
						player_alive = battle(*this->player_, rat_king);
						tut_status++;
					}
					break;
				case 2:
					inv_menu->enter();
					break;
				case 3:
					if(tut_status <= 1){
						if (player_->equipped_armor() != nullptr || player_->equipped_armor() != nullptr) {
							player_alive = battle(*this->player_, rat);
							this->menu_string = "1)Explore the Darkness;"+end_string;
							tut_status = 2;
						}
					}
					else if(tut_status == 4){
						this->menu_string = "1)Enter Shop;" + end_string;
					}
					else if(tut_status == 5){
						this->menu_string = "1)Fight Giant Rat;" + end_string;
					}
					break;
				case 4:
					std::cout << "Not Yet implemented";
					pause();
					break;
			}
			if(!player_alive || tut_status == 7) {
				break;
			}
		}
	}
};


#endif //ITP298_CAPSTONE_TUTORIAL_MENU_HXX

