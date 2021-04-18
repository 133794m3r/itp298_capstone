/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/5/21.
*
*/
#include "../includes.hxx"
#include "../classes/items/itembase.hxx"
#include "../classes/items/weapon.hxx"
#include "../classes/items/armor.hxx"
int main(){
    Item temp_item("oil lamp",0,4,0,10);
    std:: cout << "Your item is an: " << temp_item.get_name() << std::endl;
    std:: cout << "Oil lamp has an ID of: " << temp_item.get_id() << std::endl;
    std:: cout << "Oil lamp is type: " << temp_item.get_type() << std::endl;
    std:: cout << "Oil lamp has a sell value of: " << temp_item.get_value() << std::endl;
    std:: cout << "Oil lamp's level is " << temp_item.get_level() << std::endl;
    std:: cout << "Oil lamp is a tier " << temp_item.get_tier() << std::endl;
    Weapon temp("Master Sword", 0, 2, 3, 0,5 );
    std:: cout << "Your Item is type: " << temp.get_type() << std::endl;
    std:: cout << "Your Weapon has a name of: " << temp.get_name() << std::endl;
    std:: cout << "Master Sword has " << temp.get_damage() << " " << "Attack Power" << std::endl;
    std:: cout << "Master Sword has a sell value of: " << temp.get_value() << " " << "gold" << std::endl;
    std:: cout << "Master Sword has an ID of: " << temp.get_id() << std::endl;
    std:: cout << "Master Sword is a tier " << temp.get_tier() << std::endl;
    std:: cout << "Master Sword's level is " << temp.get_level() << std::endl;
    Armor temp_armor("Plate",0,1,3,0,20);
    std:: cout << "Your item is type: " << temp_armor.get_type() << std::endl;
    std:: cout << "Your Armor is made of: " << temp_armor.get_name() << std::endl;
    std:: cout << "Your Armor has an ID of: " << temp_armor.get_id() << std::endl;
    std:: cout << "Your Armor provides: " << temp_armor.get_defense() << " " << "Defense" << std::endl;
    std:: cout << "Your Armor is worth: " << temp_armor.get_value() << " " << "Gold" << std::endl;
    std:: cout << "Your Armor's level is: " << temp_armor.get_level() << std::endl;
    std:: cout << "Your Armor is tier: " << temp_armor.get_tier() << std::endl;
    }
