/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/26/21.
*
*/

#ifndef ITP298_CAPSTONE_ITEMS_HXX
#define ITP298_CAPSTONE_ITEMS_HXX
//the items below are solely here for the tutorial so their use in the real game is questionable.
//as you'd not have a junk item of level 2.
Weapon stick("Sharp Stick",1,1);
Armor shirt("Thick Shirt",1,1);
Potion basic_potion("Basic");
Item paper_crown("Small Paper Crown",4,2);
//this is a super hack but it'll work for now.
//eventually creating a new item globally will add it to this vector but for now this works. Eventual plan is to index
//into this vector to figure out which item they have.
std::vector<Item *> ALL_ITEMS_({&stick, &shirt, &basic_potion, &paper_crown});
#endif //ITP298_CAPSTONE_ITEMS_HXX
