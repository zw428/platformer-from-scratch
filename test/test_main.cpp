#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int test()
{
	return 5;
}

TEST_CASE( "test", "[test]" )
{
	REQUIRE( test() == 5 );
}
