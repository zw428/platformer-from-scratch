#include <catch2/catch.hpp>
#include "attack_manager.h"
#include "anim_handler.h"

class delayed_attack_tmp : public delayed_attack
{
	void perform() {};
};

TEST_CASE( "can't move while attacking", "[attack_manager]" )
{
	delayed_attack_tmp* da = new delayed_attack_tmp;

	attack_manager am;

	anim a;

	am.set_up_attack(da, a);

	anim_handler ah;

	am.think(ah, true, 0, false, false, false);

	CHECK(am.can_move() == 0);
}

TEST_CASE( "can move after attack is over", "[attack_manager]" )
{
	delayed_attack_tmp* da = new delayed_attack_tmp;

	da->action.delay(2);

	attack_manager am;

	anim a;

	am.set_up_attack(da, a);

	anim_handler ah;

	am.think(ah, true, 0, false, false, false);

	CHECK(am.can_move() == 0);

	am.think(ah, false, 0, false, false, false);

	CHECK(am.can_move() == 0);

	am.think(ah, false, 0, false, false, false);

	CHECK(am.can_move() == true);
}
