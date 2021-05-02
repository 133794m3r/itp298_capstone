/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/30/21.
*
*/
#include "../classes/fighters/player.hxx"
#include "../data/items.hxx"
#include "../main.hxx"
int main(){
	std::string prefix =
	//if we're on windows and compiling with default Visual Studio settings for CMake builds
#ifdef VISUAL_STUDIO_BUILD
	"..\\..\\..\\test_data\\";
	//otherwise we are on windows still have to change prefix
#elif NOMINMAX
	"..\\test_data\\";
#else
		//otherwise we're on a Unix based system.
	"../test_data/";
#endif
	Player player("zzz_test_user");
	player.add_item(stick);
	player.equip_weapon(stick);
	save_game(player);
	Player player2;
	int res = load_game("zzz_test_user_save_file.dat",player2);
	std::cout << "\x1b[1mSAVE TESTS\x1b[0m\n";
	std::cout << "Save file creation/loading test....\n";


	unsigned int tests_passed = 0;
	unsigned int tests_failed = 0;
	if(res != 0){
		std::cout << "Test failed. Wasn't able to load file!";
		tests_failed++;
	}
	else {
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
	std::cout << std::endl;

	std::cout << "Invalid save format tests\n";
	std::cout << "Bad Hash Test -- ";
	int result = load_game(prefix+"bad_hash_save_file.dat",player2);
	if(result != 5 ){
		tests_failed++;
		std::cout << "Expected code: 5 but we got " << result;
	}
	else{
		std::cout << "Test passed.";
		tests_passed++;
	}
	std::cout << std::endl;

	//bad hash
	std::cout << "No hash Test -- ";
	result = load_game(prefix+"no_hash_save_file.dat",player2);
	if(result != 5 ){
		tests_failed++;
		std::cout << "Expected code: 5 but we got " << result;
	}
	else{
		std::cout << "Test passed.";
		tests_passed++;
	}
	std::cout << std::endl;

	//no file
	std::cout << "No File test --";
	result = load_game(prefix+"..._save_file.dat",player2);
	if(result != 2 ){
		tests_failed++;
		std::cout << "Expected code: 2 but we got " << result;
	}
	else{
		std::cout << "Test passed.";
		tests_passed++;
	}
	std::cout << std::endl;

	std::cout << "Bad name test --";
	//bad name
	result = load_game(prefix+"test_data/bad_name.csv",player2);
	if(result != 1 ){
		tests_failed++;
		std::cout << "Expected code: 5 but we got " << result;
	}
	else{
		std::cout << "Test passed.";
		tests_passed++;
	}
	std::cout << std::endl;

	std::cout << "Bad number of items test -- ";
	//bad number of items
	result = load_game(prefix+"bad_number_of_items_save_file.dat",player2);
	if(result != 6 ){
		tests_failed++;
		std::cout << "Expected code: 6 but we got " << result;
	}
	else{
		std::cout << "Test passed.";
		tests_passed++;
	}
	std::cout << std::endl;

	std::cout << "Equipped Armor Test -- ";
	//has equipped item
	result = load_game(prefix+"equipped_armor_save_file.dat",player2);
	if(result != 0 ){
		tests_failed++;
		std::cout << "Expected code: 0 but we got " << result;
	}
	else{
		std::cout << "Test passed.";
		tests_passed++;
	}
	std::cout << std::endl;

	std::cout << "\n\x1b[1mResult\x1b[0m\n\x1b[" << BRIGHT_GREEN_TXT << "mPASSED:" << tests_passed << " \x1b[" << BRIGHT_RED_TXT << "mFAILED:" << tests_failed << "\x1b[0m out of " << (tests_passed+tests_failed) << " total tests.\n" << std::endl;
	return (tests_failed != 0)?1:0;
}