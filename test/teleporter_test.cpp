#include "catch.hpp"
#include "../teleporter.h"
#include "../object.h"
#include "../manager.h"

class teleporter_tmp : public object
{
public:
	bool think() { return false; };
};

TEST_CASE( "teleporter teleports things when nothing is in the way", "[teleporter]" )
{
	manager::instance()->init( true );
	manager::instance()->get_map()->init(1024,1024);

	teleporter_tmp* obj = new teleporter_tmp;

	obj->x(5);
	obj->y(5);

	manager::instance()->get_map()->add_object(obj);

	teleport(obj,12,12);

	CHECK( obj->x() == 12 );
	CHECK( obj->y() == 12 );

	manager::destroy();
}

TEST_CASE( "teleporter doesn't teleports things when something is in the way", "[teleporter]" )
{
	manager::instance()->init( true );
	manager::instance()->get_map()->init(1024,1024);

	teleporter_tmp* obj = new teleporter_tmp;

	obj->x(5);
	obj->y(5);
	obj->w(5);
	obj->h(5);
	
	manager::instance()->get_map()->add_object(obj);
	
	teleporter_tmp* obj2 = new teleporter_tmp;

	obj2->x(100);
	obj2->y(100);
	obj2->w(100);
	obj2->h(100);

	manager::instance()->get_map()->add_object(obj2);

	teleport(obj,100,100);

	CHECK( obj->x() == 5 );
	CHECK( obj->y() == 5 );

	manager::destroy();
}
