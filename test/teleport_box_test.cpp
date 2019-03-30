#include <catch2/catch.hpp>
#include "teleport_box.h"
#include "object.h"

TEST_CASE( "teleport box teleports objects", "[teleport_box]" )
{
	teleport_box t;

	t.set_dest( 12, 12 );

	box_object bo;
	bo.dimens.x(5);
	bo.dimens.y(5);

	t.action(&bo);

	CHECK( bo.dimens.x() == 12 );
	CHECK( bo.dimens.y() == 12 );
}
