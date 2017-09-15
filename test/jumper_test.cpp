#include "catch.h"
#include "../jumper.h"

TEST_CASE( "jumper constructor initializes stuff", "[jumper]" )
{
	jumper j;

	CHECK( j.jump_vel_1() == 9 );
	CHECK( j.jump_vel_2() == 8 );
	CHECK( j.times_jumped() == 0 );
}

TEST_CASE( "jumper setters/getters work", "[jumper]" )
{
	jumper j;

	j.jump_vel_1(10);
	j.jump_vel_2(11);

	CHECK( j.jump_vel_1() == 10 );
	CHECK( j.jump_vel_2() == 11 );
}

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
