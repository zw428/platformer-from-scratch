#include "catch.h"
#include "../alive.h"
#include "../attack.h"

TEST_CASE( "alive setters and getters work", "[alive]" )
{
	SECTION( "setters" )
	{
		alive a;
		a.health(5);

		REQUIRE( a.health() == 5 );
	}

	SECTION( "getters" )
	{
		alive a;
		a.health(5);

		REQUIRE( a.health() == 5 );
	}

	SECTION( "health doesn't drop below 0" )
	{
		alive a;
		a.health(10);

		attack att;
		att.damage(15);

		a.receive_attack( att );

		REQUIRE( a.health() == 0 );
	}
}

TEST_CASE( "alive constructor initializes health to 1" )
{
	alive a;
	REQUIRE( a.health() == 1 );
}
