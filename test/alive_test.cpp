#include "catch.h"
#include "../alive.h"
#include "../attack.h"

TEST_CASE( "alive health doesn't drop below 0", "[alive]" )
{
	alive a;
	a.health(10);

	attack att;
	att.damage(15);

	a.receive_attack( att );

	CHECK( a.health() == 0 );
}
