/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include "main.hxx"
int main(int argc, char *argv[]) {
	clear_and_move_top();
	unsigned int option;
	int result;
	if(argc == 2){
		if(strncmp(argv[1],"-h",2) == 0){
			std::cout << "\nprogram use " << argv[0];
			std::cout << " {SAVE_FILE_TO_LOAD}. Or -h to see this message. If no argument is given it'll immediately go into the game loading.\n The game does basic checks to make sure it's loading a valid save file but the rest is up to you.\n\n";
			return 0;
		}
		else {
			Player player;
			result = load_game(argv[1], player);
			if (result != 0) {
				std::cout << "Thanks for playing but the game isn't ready yet.\n";
				return 0;
			}
			else {
				return result;
			}
		}
	}
	redraw_main();
	std::cout << "\x1b[1mSelection\x1b[22m: ";
	option = valid_option(1,3);
	if(option == 1) {
		std::string player_name;
		std::cout << "Enter your name: ";
		std::cin >> player_name;
		if(player_name.size() > 50){
			move_and_clear_up(1);
			while(player_name.size() > 50 && !player_name.empty()){
				std::cout << "Name is too long! Max is 50 characters\n";
				std::cout << "Reenter your name: ";
				std::cin >> player_name;
				move_and_clear_up(3);
			}
		}
		if(player_name.empty()){
			exit(0);
		}
		Player player(player_name);
		InventoryMenu player_inv(&player);
		TutorialMenu tutorial(player, player_inv);
		tutorial.enter();
		std::cout << "You take the Rat King's paper crown and place it in your pocket. You hear someone coming....\nIt is a powerful presence. You hide in the shadows. As you skulk away you hear them say \"What have they done to you Tina, and your little children! I'll get that evil person who has killed my precious baby Tina.\n\nTune in next time for an actual game!";
		//save their game
		save_game(player);
	}
	else if(option == 2){
		std::cout << "Enter your character's name: ";
		std::string filename;
		std::cin >> filename;
		Player player;
		load_game(filename+"_save_file.dat",player);
		std::cout << "Your file loaded correctly but the game isn't ready yet, so please try again later!";
		return 0;
	}
	else{
		return 0;
	}
}
