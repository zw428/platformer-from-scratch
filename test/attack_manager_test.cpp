#include "catch.h"
#include "../attack_manager.h"

class delayed_attack_tmp : public delayed_attack
{
	void perform() {};
};

TEST_CASE( "can't move while attacking", "[attack_manager]" )
{
	delayed_attack_tmp* da = new delayed_attack_tmp;

	attack_manager am;

	am.set_up_attack(da);

	am.think(true, 0, false, false, false);

	CHECK(am.can_move() == 0);
}

TEST_CASE( "can move after attack is over", "[attack_manager]" )
{
	delayed_attack_tmp* da = new delayed_attack_tmp;

	da->action.delay(2);

	attack_manager am;

	am.set_up_attack(da);

	am.think(true, 0, false, false, false);

	CHECK(am.can_move() == 0);

	am.think(false, 0, false, false, false);

	CHECK(am.can_move() == 0);

	am.think(false, 0, false, false, false);

	CHECK(am.can_move() == true);
}
