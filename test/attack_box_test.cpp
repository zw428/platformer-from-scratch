#include "catch.h"
#include "../attack_box.h"
#include "../object.h"
#include "../alive.h"
#include "../vel_accel.h"

class attack_box_tmp : public object, public alive, public vel_accel
{
	bool think() { return false; };
};

TEST_CASE( "attack_box setters/getters work", "[attack_box]" )
{
	attack_box_tmp t;

	t.health(20);

	attack_box att_b;

	attack att;
	att.damage(17);
	att_b.set_attack(att);

	att_b.action( &t );

	CHECK( t.health() == 3 );
}

TEST_CASE( "attack_box damages object", "[attack_box]" )
{
	attack_box_tmp t;

	t.health(5);

	attack_box att_b;

	attack att;
	att.damage(1);
	att_b.set_attack(att);

	att_b.action( &t );

	CHECK( t.health() < 5 );
}

TEST_CASE( "attack_box knocks back object", "[attack_box]" )
{
	attack_box_tmp t;

	t.h_speed(0);
	t.v_speed(0);

	attack_box att_b;

	attack att;
	att.knockback(1);
	att_b.set_attack(att);

	att_b.action( &t );

	CHECK( t.h_speed() != 0 );
	CHECK( t.v_speed() != 0 );
}
