#include "catch.hpp"
#include "../attack_box.h"
#include "../object.h"
#include "../alive.h"
#include <iostream>

TEST_CASE( "attack_box damages object", "[attack_box]" )
{
	class tmp : public object, public alive
	{
		bool think() { return false; };
	};
	
	tmp t;

	t.health(5);

	attack_box att_b;

	att_b.damage(3);

	object* obj = dynamic_cast<object*>(&t);

	att_b.action( obj );

	REQUIRE( t.health() == 2 );
}

TEST_CASE( "attack_box knocks back object", "[attack_box]" )
{
	class tmp : public object
	{
		bool think() { return false; };
	};

	tmp t;

	t.h_speed(0);
	t.v_speed(0);

	attack_box att_b;

	att_b.knockback(10);

	object* obj = dynamic_cast<object*>(&t);

	att_b.action( obj );

	REQUIRE( t.h_speed() != 0 );
	REQUIRE( t.v_speed() != 0 );
}
