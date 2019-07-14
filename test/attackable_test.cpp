#include <catch2/catch.hpp>
#include "attackable.h"

TEST_CASE( "attackable health doesn't drop below 0", "[attackable]" )
{
	attackable a;
	a.health(10);

	attack att;
	att.damage(15);

	a.receive_attack( att );

	CHECK( a.health() == 0 );
}

TEST_CASE( "attackable returns true if health is 0", "[attackable]" )
{
	attackable a;
	a.health(0);

	CHECK( a.think_more() );
}
