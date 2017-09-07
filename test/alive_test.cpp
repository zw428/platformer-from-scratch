#include "catch.hpp"
#include "../alive.h"
#include "../attack.h"

TEST_CASE( "alive setters and getters work", "[alive]" )
{
	SECTION( "constructor" )
	{
		alive a;

		REQUIRE( a.health() == 1 );
	}

	SECTION( "setters" )
	{
		alive a;
		a.health(5);

		REQUIRE( a.health() == 5 );
	}

	SECTION( "const getters" )
	{
		alive a;
		a.health(5);
		const alive& a_const = a;

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
