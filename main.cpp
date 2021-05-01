/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include "main.hxx"
int main(int argc, char *argv[]) {
	clear_and_move_top();
	redraw_main();
	unsigned int option;
	if(argc == 2){
		load_game(argv[1]);
		std::cout << "Thanks for playing but the game isn't ready yet.";
	}
	std::cout << "\x1b[1mSelection\x1b[22m: ";
	option = valid_option(1,3);
	if(option == 1) {
		std::string player_name;
		std::cout << "Enter your name: ";
		std::cin >> player_name;
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
		load_game(filename+"_save_file.dat");
		std::cout << "Your file loaded correctly but the game isn't ready yet, so please try again later!";
		return 0;
	}
	else{
		return 0;
	}
}
