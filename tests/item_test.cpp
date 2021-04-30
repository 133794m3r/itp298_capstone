/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/5/21.
*
*/
#include "../includes.hxx"
#include "../classes/items/item_base.hxx"
#include "../classes/items/weapon.hxx"
#include "../classes/items/armor.hxx"
#include <string>

int main(){
	unsigned short tests_failed = 0;
	std::string item_stats = "id = 0 Name = oil lamp Type = 0 Tier = 4 Value = 95 Level = 10";
	std::string weapon_stats = "id = 1 Name = Master Sword Type = 1 Damage = 19 Value = 60 Tier = 0 Level = 5";
	std::string armor_stats = "id = 2 Name = Plate Defense = 60 Type = 2 Tier = 1 Value = 165 Level = 20";

	Item temp_item("oil lamp",0,4,10);
	Weapon temp_weapon("Master Sword", 0,5);
	Armor temp_armor("Plate", 1,20);

	std::cout << temp_item.toString() << std::endl;
	std::cout << item_stats << std::endl;
	std::cout << temp_weapon.toString() << std::endl;
	std::cout << weapon_stats << std::endl;
	std::cout << temp_armor.toString() << std::endl;
	std::cout << armor_stats << std::endl;

	if (item_stats !=  temp_item.toString() ){
		std::cout << "Item creation test failed " << std:: endl;
		tests_failed++;
	}
	else{
		std::cout << "Base Item test succeeded." << std::endl;
	}
	if (weapon_stats != (temp_weapon.toString())) {
		std::cout << "Weapon creation test failed " << std:: endl;
		tests_failed++;
	}
	else{
		std::cout << "Weapon Test succeeded." << std::endl;
	}

	if ((armor_stats) != temp_armor.toString() ){
			std::cout << "Armor creation test failed " << std:: endl;
			tests_failed++;
	}
	else{
		std::cout << "Armor test succeeded." << std::endl;
	}

	std::cout << "Passed " << 3 - tests_failed << "/3" << std::endl;
		if(tests_failed != 0){
			return 1;
		}
		else
			return 0;
}

