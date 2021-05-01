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
	Player player("zzz_test_user");
	player.add_item(stick);
	save_game(player);
	Player player2;
	int res = load_game("zzz_test_user_save_file.dat",player2);
	if(res != 0){
		std::cout << "something's broken";
		return 1;
	}
	std::cout << (std::string) player2 << std::endl;
	return 0;
}