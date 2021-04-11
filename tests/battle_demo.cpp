/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include "../random.h"
#include "../menus/battle.hxx"
int main(){
	//something to be done here.
	Mob mob("Fish",1,1);
	Player player("Jimmy",1);
	Mob boss("Boss",8,2);
	show_all_stats(boss);
	show_all_stats(mob);
	show_all_stats(player);
	battle(player,mob);
	return 0;
}
