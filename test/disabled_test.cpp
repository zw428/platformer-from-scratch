#include <catch2/catch.hpp>
#include "disabled.h"

TEST_CASE( "disabled can be disabled for a set amount of time", "[disabled]" )
{
	disabled d;

	d.disable(5);

	CHECK( d.is_disabled() == true );

	for ( unsigned i=0; i < 5; i++ )
	{
		d.handle_disabled();
	}

	CHECK( d.is_disabled() == false );
}
