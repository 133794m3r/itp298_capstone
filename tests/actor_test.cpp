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
	unsigned short tests_failed = 0;

	//create a basic actor
	Actor base_actor("Test");
	//have to do this since I couldn't figure out a good way of doing this without adding
	//another property to the actor
//	base_actor.set_level(1);
	//create a basic player
	Player tmp_player("Player");
	//create a basic mob.
	Mob tmp_mob("Spawn of Death");
	unsigned int tmp_player_hp = tmp_player.get_hp();
	unsigned int tmp_mob_hp = tmp_mob.get_hp();
	//test the first actor build
	if( "id: 0 Test hp:15/15 str:5/5 def:3/3" != (std::string) base_actor){
		std::cout << "Base actor test failed. got '" << (std::string) base_actor;
		std::cout << "\nbut we expected 'id: 0 Test hp:15/15 str:5/5 def:3/3'\n";
		tests_failed++;
	}
	else
		std::cout << "Base actor test succeeded.\n";
	//same with the player
	if("id: 65535 Player hp:20/20 str:5/5 def:4/4 xp:0 g:100" != (std::string) tmp_player){
		std::cout << "player creation test failed\n";
		std::cout << "Expected 'id: 65535 Player hp:20/20 str:5/5 def:4/4 xp:0 g:100' but we got '";
		std::cout << (std::string) tmp_player << '\n';
		tests_failed++;
	}
	else
		std::cout << "Player creation test Passed\n";
	//and mob
	if( "id: 2 Spawn of Death hp:16/16 str:8/8 def:3/3 xp:7 g:5 tier: 1 / normal" != (std::string) tmp_mob){
		std::cout << "mob creation test failed \n";
		std::cout << "Expected 'id: 2 Spawn of Death hp:16/16 str:8/8 def:3/3 xp:7 g:5 tier: 1 / normal' but we got '";
		std::cout << (std::string) tmp_mob << '\n';
		tests_failed++;
	}
	else
		std::cout << "Mob creation test passed\n";

	//test the damage method
	base_actor.damage(22);
	//should've killed them.
	if(!base_actor.is_alive()) {
		std::cout << "Actor death test succeeded\n";
	}
	else {
		std::cout << "Actor death test failed\n";
		tests_failed++;
	}

	//attack the base object.
	tmp_player.attack(tmp_mob);
	unsigned int expected_hp = tmp_mob_hp - (tmp_player.get_str() - tmp_mob.get_def());
	std::cout << "Actor targetting mob test ";
	if(tmp_mob.get_hp() != expected_hp ){
		std::cout << "failed. Mob HP wrong expected " << expected_hp << " but got " << tmp_mob.get_hp() <<'\n';
		tests_failed++;
	}
	else{
		std::cout << "test passed." << std::endl;
	}

	//attack the player this time
	tmp_mob.attack(tmp_player);
	expected_hp = (tmp_player_hp - (tmp_mob.get_str() - tmp_player.get_def()) );
	std::cout << "Mob targeting player test ";
	if(tmp_player.get_hp() != expected_hp ){
		std::cout << "failed. Expected " <<  expected_hp << " but got " << tmp_player.get_hp() << '\n';
		tests_failed++;
	}
	else{
		std::cout << "passed.\n";
	}
	//test the tiers and scaling.
	Mob boss("Bossman",6,5);
	std::cout << "Boss creation/scaling/tier test ";
	if((std::string) boss != "id: 3 Bossman hp:115/115 str:42/42 def:24/24 xp:192 g:178 tier: 6 / boss"){
		std::cout << "failed. Expected 'id: 3 Bossman hp:115/115 str:42/42 def:24/24 xp:192 g:178 tier: 6 / boss' but we got '" << (std::string) boss << "'\n";
		tests_failed++;
	}
	else
		std::cout << "passed.\n";

	std::cout << "Junk Mob creation test\n";
	Mob junk_mob("Junk",0);
	if((std::string) junk_mob != "id: 4 Junk hp:13/13 str:5/5 def:2/2 xp:4 g:2 tier: 0 / trash"){
		std::cout << "Test failed: Expected 'id: 4 Junk hp:13/13 str:5/5 def:2/2 xp:4 g:2 tier: 0 / trash' but we got " << (std::string) junk_mob << '\n';
		tests_failed++;
	}
	std::cout << "Passed " << 7 - tests_failed << "/7" << std::endl;

	if(tests_failed != 0)
		return 1;
	else
		return 0;

}
