#include "catch.h"
#include "../box_object.h"

TEST_CASE( "box_object moves children with it", "[box]" )
{
	box_object bo;

	box_object bo2;

	bo.add_child(&bo2);

	bo.dimens.x(100);
	bo.dimens.y(200);
	bo.speeds.h_speed(6);
	bo.speeds.v_speed(-3);

	bo2.dimens = bo.dimens;

	bo.think();

	CHECK(bo2.dimens.x() == 106);
	CHECK(bo2.dimens.y() == 197);
}
