/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*
*/
#include "../includes.hxx"
#include "../classes/fighters/actor.hxx"
#include "../classes/fighters/mob.hxx"
#include "../classes/fighters/player.hxx"
int main(){
	//create a basic actor
	Actor base_actor("Test");
	//create a baisc player
	Player tmp_player("Player");
	//test this method to make sure the actor was created right.
	show_all_stats(base_actor);
	//test the damage method
	int damaged = base_actor.damage(22);
	//should've killed them.
	if(damaged <0)
		std::cout << "Killed " << base_actor.get_name() << std::endl;
	else
		std::cout << "Did " << damaged << " damage." << std::endl;
	//make sure they're dead.
	show_cur_stats(base_actor);
	//recreate b/c no setter for _hp.
	base_actor = Actor("Test");
	//create a basic mob.
	Mob tmp_mob("Spawn of Death");
	//attack the base object.
	tmp_player.attack(base_actor);
	//show that it did in fact attack them with the player's stats
	show_all_stats(tmp_player);
	//show the changed stats
	show_cur_stats(base_actor);
	//attack the player this time
	base_actor.attack(tmp_player);
	//show changes
	show_cur_stats(tmp_player);
    return 0;
}

