/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include "../random.h"
#include "../menus/battle.hxx"
int main(){
	std::cout << "\x1b[" << BRIGHT_WHITE_TXT << ";" << BLACK_BG << "m";
	//something to be done here.
	Mob mob("Fish",1,1);
	Player player("Jimmy",2);
	Mob boss("Fishmonger",6,2);
	show_all_stats(boss);
	show_all_stats(mob);
	show_all_stats(player);
	battle(player,mob);
	show_all_stats(player);
	return 0;
}
