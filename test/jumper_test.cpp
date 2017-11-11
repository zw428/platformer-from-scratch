#include "catch.h"
#include "../jumper.h"

TEST_CASE( "jumper correctly handles jumping from the ground", "[jumper]" )
{
	jumper j;

	CHECK( j.times_jumped() == 0 );

	j.handle_jumping(true,true);
	CHECK( j.times_jumped() == 1 );

	j.handle_jumping(false,true);

	CHECK( j.times_jumped() == 1 );

	j.handle_jumping(false,false);

	CHECK( j.times_jumped() == 1 );

	j.handle_jumping(false,true);

	CHECK( j.times_jumped() == 2 );

	j.handle_jumping(false,true);

	CHECK( j.times_jumped() == 2 );

	j.handle_jumping(true,false);

	CHECK( j.times_jumped() == 0 );
}

TEST_CASE( "jumper correctly handles jumping after falling", "[jumper]" )
{
	jumper j;

	j.handle_jumping(false,false);
	CHECK( j.times_jumped() == 1 );

	j.handle_jumping(false,true);
	CHECK( j.times_jumped() == 2 );
}
