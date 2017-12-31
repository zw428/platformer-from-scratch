#include "catch.h"
#include "../attack.h"
#include "../alive.h"

TEST_CASE( "alive health doesn't drop below 0", "[alive]" )
{
	alive a;
	a.health(10);

	attack att;
	att.damage(15);

	a.receive_attack( att );

	CHECK( a.health() == 0 );
}
