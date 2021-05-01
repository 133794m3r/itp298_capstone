/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/
#ifndef ITP298_CAPSTONE_MOB_HXX
#define ITP298_CAPSTONE_MOB_HXX

//have a custom structure for the rewards themselves.
struct MobRewards{
	unsigned int gold = 0;
	unsigned int xp = 0;
	std::vector<std::pair<Item *,unsigned int>> items;
};

#include "actor.hxx"
#include "../containers/loot_table.hxx"
class Mob : public Actor {
  private:
	//the xp to be awarded and gold be awarded upon death.
	unsigned long xp_;
	unsigned int gold_;
	//the tier strings
	const static std::string tier_str[7];

	/*
	 * type is based upon the following list.
	 * 0 = trash-tier, 1 = normal, 2 = rare, 3 = elite, 4 = rare elite, 5 = mini-boss, 6 = boss
	 * they get a bonus to all stats based upon their tier(or reduced for trash).
	 * The stat bonus makes it as if they are of a higher level than they really are like so.
	 * Bosses use their own rules and thus don't use the normal formula below but isntead start as "boss" number.
	 * stats = set_stats(this->lvl_+ (TIER - 1))
	 * plus the bonuses when creating the mob are modified to gain (TIER-1)*0.1.
	 * So the bonus_hp_ value would be increased by 1.2 for an elite mob. For a trash mob their
	 * stats would all be reduced by 10%. Plus their level would be one less than the
	 * currently set one.
	 */

	//a short to make C++ not try to make it be a string when doing stream operations.
	unsigned short tier_;
	//loot table
	LootTable loot_table;

	/**
	 * Sets the amount of gold that this mob should reward upon it's death.
	 */
	void set_gold(){
		unsigned int dl = this->lvl_ + 1;
		double gm = 1.9;
		double glm;
		double bvm;
		if(dl < 10){
			gm = 5.9;
			glm = 1.9;
			bvm = 6.8;
		}
		else if(dl < 40){
			gm = 6.0;
			glm = 1.85;
			bvm = 7.0;
		}
		else if(dl < 91){
			gm = 1.95;
			glm = 2.0;
			bvm = 50;
		}
		else if(dl < 151){
			glm = 2.2;
			bvm = 70.0;
		}
		else if(dl < 199){
			glm = 2.4;
			bvm = 100.0;
		}
		else{
			glm = 4.0;
			bvm = 120.0;
		}
		this->gold_ = static_cast<unsigned int>((((this->xp_*glm)-((dl / gm) * bvm))) * 0.5);
	}
  public:

	//initialize the Mob class. Explicit since it can be called with just 1 parameter. Also initialize properties with parent class' constructor.
	explicit Mob(std::string name="Mob",unsigned short tier=1, unsigned short level=1,
			  double bonus_hp=0.00, double bonus_str=0.0, double bonus_def=0.0)
			  :Actor(std::move(name),level,bonus_hp+((tier-1.0)/20),
			bonus_str+((tier-1.0)/100),bonus_def+((tier-1.0)/80),16,6,3,1) {
		unsigned int tmp = this->lvl_ + 1;
		//based on other formulas this should make the curve OK.
		//tier will modify the two formulas below eventually
		this->xp_ = std::lround( tmp* ((tmp*0.79 )+1.2));
		this->set_gold();
		this->tier_ = tier;
		this->set_level(level);
	}


	/**
	 * Sets all stats for the object based upon the level we set.
	 * @param level The level that we're going to be basing scaling on.
	 */
	void set_level(unsigned short level) override{
		double modifier =  (1 + ( (this->tier_<5)?(this->tier_-1)/29.0:(this->tier_-1)/27.0 ));
		double dif;
		//if it's the same just do nothing.
		if(level == this->lvl_)
			dif = this->lvl_ - 1;
		else if(level > this->lvl_)
			dif = level - this->lvl_;
		else
			dif = this->lvl_ - level;
		dif += (this->tier_-1)/6;
		//when they modify the level change the stats to the proper values.
		this->base_hp_ += std::lround( (this->bonus_hp_+1.0)*13.1*modifier*dif)+(this->tier_-1);
		this->base_str_ += std::lround( ((this->bonus_str_+1.0)*4.0*modifier*dif)+((this->tier_)*2));
		this->base_def_ += std::lround( ((this->bonus_def_+1.0)*3.125*modifier*dif)+((this->tier_-1)/3));
		//then set the current stats from the base.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}

	/**
	 * Gets the tier of the mob.
	 * @return The tier of the mob.
	 */
	unsigned short get_tier() const{
		return this->tier_;
	}

	/**
	 * Returns the rewards upon death.
	 *
	 * @return A custom struct of the xp, gold, and the items that they can expect.
	 */
	MobRewards rewards(){
		MobRewards rewards;
		rewards.xp = this->xp_;
		rewards.gold = this->gold_;
		if(this->loot_table.inventory_quantity() != 0)
			rewards.items = this->loot_table.award_items();
		return rewards;
	}

	/**
	 * Add items to the mob's loot table.
	 * @param items The items to add
	 * @param quantity The number for each
	 * @param chances The chance of each appearing
	 */
	void add_items(std::vector<Item *> items, std::vector<unsigned int> quantity, std::vector<double> chances){
		for(unsigned int i=0;i<chances.size();i++){
			this->loot_table.add_item(*items[i], quantity[i],chances[i]);
		}
	}

	/**
	 * Add a single item
	 * @param item Item to add
	 * @param quantity The number to add
	 * @param chance The chance of rewarding it
	 */
	void add_item(Item &item, unsigned int quantity=1, double chance = 1.0){
		this->loot_table.add_item(item,quantity,chance);
	}

	/**
	 * Converts the object into a string.
	 *
	 * @return The object stringified.
	 */
	operator std::string(){
		std::stringstream ss;
		ss << "id: " << this->id << " " << this->name_ << " hp:" <<this->hp_ << "/" << this->base_hp_ <<
		   " str:" << this->str_ << "/" << this->base_str_ << " def:" << this->def_ << "/"
		   << this->base_def_ << " xp:" << this->xp_ << " g:" << this->gold_ << " tier: " << this->tier_
		   << " / " << tier_str[this->tier_];
		return ss.str();
	}
};
//the tiers but in string form.
const std::string Mob::tier_str[7] =  {"trash", "normal", "rare", "elite", "rare elite", "mini-boss", "boss"};

#endif //ITP298_CAPSTONE_MOB_HXX
