/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
#include "../menus/battle.hxx"
int main(){
	//basic demo file used in testing.
	std::cout << "\x1b[" << BRIGHT_WHITE_TXT << ";" << BLACK_BG << "m";
	//something to be done here.
	Mob mob("Fish",1,1);
	Player player("Jimmy",2);
	Mob boss("Fishmonger",6,2);
	Potion potion("Basic");
	Armor cloth_shirt("Cloth Shirt",0,1);
	Weapon rusty_sword("Rusty Sword",0,1);
	Item paper_crown("Paper Crown",0,4,1);
	mob.add_items({&cloth_shirt, &rusty_sword,&paper_crown},{1,1,1},{1.0, 1.0,1.0});
	player.add_item(potion,2);
	player.equip_armor(cloth_shirt);
	player.equip_weapon(rusty_sword);
	battle(player,mob);
	show_all_stats(player);
	return 0;
}
