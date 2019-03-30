#include <catch2/catch.hpp>
#include "teleporter.h"
#include "object.h"
#include "manager.h"

TEST_CASE( "teleporter teleports things when nothing is in the way", "[teleporter]" )
{
	manager::instance()->init( true );
	manager::instance()->the_map.init(1024,1024);

	box_object* obj = new box_object;

	obj->dimens.x(5);
	obj->dimens.y(5);

	manager::instance()->the_map.add_object(obj);

	teleport(obj,12,12);

	CHECK( obj->dimens.x() == 12 );
	CHECK( obj->dimens.y() == 12 );

	manager::destroy();
}

TEST_CASE( "teleporter doesn't teleports things when something is in the way", "[teleporter]" )
{
	manager::instance()->init( true );
	manager::instance()->the_map.init(1024,1024);

	box_object* obj = new box_object;

	obj->dimens.x(5);
	obj->dimens.y(5);
	obj->dimens.w(5);
	obj->dimens.h(5);

	manager::instance()->the_map.add_object(obj);

	box_object* obj2 = new box_object;

	obj2->dimens.x(100);
	obj2->dimens.y(100);
	obj2->dimens.w(100);
	obj2->dimens.h(100);

	manager::instance()->the_map.add_object(obj2);

	teleport(obj,100,100);

	CHECK( obj->dimens.x() == 5 );
	CHECK( obj->dimens.y() == 5 );

	manager::destroy();
}
