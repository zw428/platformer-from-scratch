#include "catch.hpp"
#include "../teleport_box.h"
#include "../object.h"

class teleport_box_tmp : public object
{
public:
	bool think() { return false; };
};

TEST_CASE( "teleport box initializes stuff in constructor", "[teleport_box]" )
{
	teleport_box t;

	CHECK( t.lifespan() == 0 );
	CHECK( t.interval() == 0 );
}

TEST_CASE( "teleport box teleports objects", "[teleport_box]" )
{
	teleport_box t;

	t.set_dest( 12, 12 );

	teleport_box_tmp tmp;
	tmp.x(5);
	tmp.y(5);

	t.action(&tmp);

	CHECK( tmp.x() == 12 );
	CHECK( tmp.y() == 12 );
}
