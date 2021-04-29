/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/22/21.
*
*/

#include "../classes/shopkeeper.hxx"
int main(){
	//test file for the shop current WIP
	//create player
	Player test_player("Jim");
	//add some gold
	test_player.add_gold(200);
	//create some items
	Armor shirt("T-shirt");
	Weapon sword("Sword");
	Item rock("Rock");
	//create shop keeper
	ShopKeeper shop_keeper("Kennel Club",{&shirt,&sword,&rock},{1000,1000,1000});
	//make player enter the shop
	shop_keeper.enter_shop(test_player);
	std::deque<unsigned short> shop_item_ids = shop_keeper.list_inventory();
	std::vector<menu_item_data> shop_items = shop_keeper.show_inventory();
	std::vector<menu_item_data> player_items = test_player.show_inventory();

	unsigned int failed_tests = 0;
	unsigned int passed_tests = 0;
	if(!player_items.empty()){
		failed_tests++;
	}
	bool over_purchase = false;
	for(unsigned short shop_item_id : shop_item_ids){
		//check if they try to buy more than they can
		over_purchase = shop_keeper.purchase_item(shop_item_id,1000);
	}
	if(over_purchase) {
		std::cout << "Test Failed: Was ";
		failed_tests++;
	}
	else{
		std::cout << "Test Passed: Wasn't ";
		passed_tests++;
	}
	std::cout << " able to purchase more than they had money for!";
	std::cout << std::endl;
	//now we simply check that they can purchase the items.
	for(unsigned short shop_item_id: shop_item_ids){
		shop_keeper.purchase_item(shop_item_id,1);
	}
	player_items = test_player.show_inventory();
	std::cout << "Player Inventory Tests";
	for(unsigned int i=0;i<player_items.size();i++){
		std::cout << "player_item Test #" << i << " ";
		if(player_items[i].item_name != shop_items[i].item_name){
			std::cout << "Failed: Expected " << shop_items[i].item_name << " but we got " << player_items[i].item_name;
			failed_tests++;
		}
		else{
			std::cout << "Passed!";
			passed_tests++;
		}
		std::cout << '\n' << "Player Item Quantity Test ";
		if(player_items[i].item_quantity != 1){
			std::cout << "Failed: Expected 1 but we got " << player_items[i].item_quantity;
			failed_tests++;
		}
		else{
			std::cout << "Passed!";
			passed_tests++;
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
	//sell everything
	for(unsigned int i=0;i<player_items.size();i++){
		shop_keeper.sell_item(shop_item_ids[i],1);
	}
	player_items = test_player.show_inventory();
	if(!player_items.empty()){
		std::cout << "Failed: Player still has items. Expected 0 items but we got " << player_items.size();
	}
	else{
		std::cout << "Passed: Player Inventory is empty!";
	}
	std::cout << std::endl;
	std::cout << "Player final gold test: ";
	if(test_player.get_gold() == 276) {
		passed_tests++;
		std::cout << "Passed!";
	}
	else{
		failed_tests++;
		std::cout << "Failed! Expected 114 but we got " << test_player.get_gold();
	}

	std::cout << "Passed " << passed_tests << "/" << (passed_tests+failed_tests) << std::endl;
	if(failed_tests != 0){
		return 1;
	}
	else{
		std::cout << "All Tests Passed!" << std::endl;
	}
	return 0;
}
