/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include "../random.h"
#include "../menus/battle.hxx"
int main(){
	//something to be done here.
	Mob mob("Fish");
	Player player("Jimmy",1,0,100);
	battle(player,mob);
	return 0;
}
