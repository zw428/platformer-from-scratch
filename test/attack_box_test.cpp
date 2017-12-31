#include "catch.h"
#include "../attack_box.h"
#include "../alive.h"

TEST_CASE( "attack_box damages object", "[attack_box]" )
{
	alive a;

	a.health(5);

	attack_box att_b;

	attack att;
	att.damage(1);
	att_b.set_attack(att);

	att_b.action( &a );

	CHECK( a.health() < 5 );
}

TEST_CASE( "attack_box knocks back object", "[attack_box]" )
{
	alive a;

	a.speeds.h_speed(0);
	a.speeds.v_speed(0);

	attack_box att_b;

	attack att;
	att.knockback(1);
	att_b.set_attack(att);

	att_b.action( &a );

	CHECK( a.speeds.h_speed() != 0 );
	CHECK( a.speeds.v_speed() != 0 );
}
