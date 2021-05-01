/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/30/21.
*
*/
#include "../classes/items/item_base.hxx"
#include "../classes/items/weapon.hxx"
#include "../classes/items/armor.hxx"
#include "../classes/items/potion.hxx"
#include "../data/items.hxx"
#include "../classes/fighters/player.hxx"
#include "../main.hxx"
int main(int argc, char *argv[]){
	if(argc == 1) {
		Player player("zzz_test_user");
		player.add_item(stick);
		save_game(player);
		Player player2 = load_game("zzz_test_user_save_file.dat");
		std::cout << "Save file creation/loading test....\n";
		unsigned int tests_passed = 0;
		unsigned int tests_failed = 0;

		if ((std::string) player == (std::string) player2) {
			std::cout << "Test passed\n";
			tests_passed++;
		}
		else {
			std::cout << "Test failed\n Expected '" << (std::string) player << "' but we got '" << (std::string) player2
					  << "'\n";
			tests_failed++;
		}
	}
	//test that we can't pass the hash test obviously.
	std::ofstream junk_file("zzy_junk_save_file.dat");
	junk_file << "Jimbo,0,0,[0,],0,1:35";
}