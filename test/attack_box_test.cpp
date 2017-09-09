#include "catch.hpp"
#include "../attack_box.h"
#include "../player.h"
#include "../object.h"
#include <iostream>

TEST_CASE( "attack_box damages object", "[attack_box]" )
{
	//player is the only class at the moment that is an alive object
	player p;

	p.health(5);

	attack_box att_b;

	att_b.damage(3);

	object* obj = dynamic_cast<object*>(&p);

	att_b.action( obj );

	REQUIRE( p.health() == 2 );
}
