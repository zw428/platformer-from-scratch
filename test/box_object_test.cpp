#include <catch2/catch.hpp>
#include "box_object.h"
#include "manager.h"

TEST_CASE( "box_object moves children with it", "[box]" )
{
	//so object destructor doesn't delete from a map that isn't there
	manager::instance()->the_map.init(512,512);

	box_object* bo = new box_object;

	manager::instance()->the_map.add_object(bo);

	box_object* bo2 = new box_object;

	bo->add_child(bo2);

	bo->dimens.x(100);
	bo->dimens.y(200);
	bo->speeds.h_speed(6);
	bo->speeds.v_speed(-3);

	bo2->dimens.x(200);
	bo2->dimens.y(100);

	bo->think();

	CHECK(bo2->dimens.x() == 206);
	CHECK(bo2->dimens.y() == 97);
}
