#include "catch.hpp"
#include "../knockback_mult.h"

TEST_CASE( "knockback_mult constructor initializes stuff", "[knockback_mult]" )
{
	knockback_mult k;

	CHECK( k.get_knockback_mult() == float(1) );
}

TEST_CASE( "knockback_mult setters/getters work", "[knockback_mult]" )
{
	knockback_mult k;

	k.set_knockback_mult(11.5);

	CHECK( k.get_knockback_mult() == float(11.5) );
}

TEST_CASE( "knockback_mult receive_attack modifies mult", "[knockback_mult]" )
{
	knockback_mult k;

	k.set_knockback_mult(10);

	attack a;
	a.damage(10);

	k.receive_attack( a );

	CHECK( k.get_knockback_mult() == float(10.1) );
}
