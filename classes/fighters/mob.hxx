/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins

*
*/
#ifndef ITP298_CAPSTONE_MOB_HXX
#define ITP298_CAPSTONE_MOB_HXX

#include "actor.hxx"

class Mob : public Actor {
private:
	//the xp to be awarded and gold be awarded upon death.
	unsigned int xp_;
	unsigned int gold_;
	//type is based upon the following list.
	// 0 = trash-tier, 1 = normal, 2 = rare, 3 = elite, 4 = rare elite, 5 = mini-boss, 6 = boss, 7 = elite boss.
	//they get a bonus to all stats based upon their tier(or reduced for trash).
	// The stat bonus makes it as if they are of a higher level than they really are like so. Bosses use their own rules and thus don't use the normal formula below but isntead start as "boss" number.
	// stats = set_stats(this->lvl_+ (TIER - 1))
	// plus the bonuses when creating the mob are modified to gain (TIER-1)*0.1. So the bonus_hp_ value would be increased by 1.2 for an elite mob. For a trash mob their stats would all be reduced by 10%. Plus their level would be one less than the currently set one.
	//a short to make C++ not try to make it be a string when doing stream operations.
	unsigned short tier_;
	//might make the gold calculator a static method but unsure as of yet.
//	static unsigned int calc_gold(unsigned int xp,unsigned int lvl){
//
//	}

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
		this->gold_ = static_cast<int>((((this->xp_*glm)-((dl / gm) * bvm))) * 0.5);
	}
public:

	//initialize the Mob class. Explicit since it can be called with just 1 parameter. Also initialize properties with parent class' constructor.
	explicit Mob(std::string name="Mob",unsigned short tier=1, unsigned short level=1, double bonus_hp=0.1, double bonus_str=0.0, double bonus_def=0.0):Actor(std::move(name),level,bonus_hp+((tier-1.0)/80),bonus_str+((tier-1.0)/120),bonus_def+((tier-1.0)/90)) {
		unsigned int tmp = this->lvl_ + 1;
		//based on other formulas this should make the curve OK.
		//tier will modify the two formulas below eventually
		this->xp_ = std::lround( tmp* ((tmp*0.79 )+1.2));
		this->set_gold();
		this->tier_ = tier;
		this->set_level(level);
	}



	void set_level(unsigned char level) override{
		level =std::lround(level * (1 + ( (this->tier_<5)?(this->tier_-1)/30.0:(this->tier_-1)/28.0 )));
		Actor::set_level(level);
	}
	/**
	 * Returns the rewards upon death.
	 *
	 * @return a std::pair struct with all of the data set.
	 */
	std::pair<unsigned int, unsigned int> rewards() {
		return std::make_pair(this->xp_, this->gold_);
	}
};


#endif //ITP298_CAPSTONE_MOB_HXX
