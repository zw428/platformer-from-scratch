#include "catch.h"
#include "../anim_handler.h"

TEST_CASE( "anim_handler sets anims properly", "[anim_handler]" )
{
	anim_handler a;

	CHECK( a.current_anim() == 0 );

	a.think( true, true, true, true );

	CHECK( a.current_anim() != 0 );
}
