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
	Actor base_actor("Test");
	Player tmp_player("Player");
	show_all_stats(base_actor);
	int damaged = base_actor.damage(22);
	if(damaged <0)
		std::cout << "Killed " << base_actor.get_name() << std::endl;
	else
		std::cout << "Did " << damaged << " damage." << std::endl;
	show_cur_stats(base_actor);
	base_actor = Actor("Test");

	tmp_player.attack(base_actor);
	show_all_stats(tmp_player);
	show_cur_stats(base_actor);
	base_actor.attack(tmp_player);
	show_cur_stats(tmp_player);
    return 0;
}

