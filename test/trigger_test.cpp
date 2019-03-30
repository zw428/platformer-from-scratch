#include <catch2/catch.hpp>
#include "trigger.h"
#include "manager.h"

class trigger_tmp : public trigger
{
public:
	bool action( box_object* bo ) { times_acted++; return false; };
	int times_acted = 0;
};

TEST_CASE( "trigger dies (returns true) when lifespan is over", "[trigger]" )
{
	trigger_tmp t;
	t.lifespan(5);

	for ( unsigned i=0; i < 5; i++ )
	{
		t.think();
	}

	CHECK( t.think() == true );
}

TEST_CASE( "trigger dies when it has a trigger limit set", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->the_map.init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->dimens.x(0);
	t->dimens.y(0);
	t->dimens.w(100);
	t->dimens.h(100);
	t->max_triggers(2);
	t->interval(0);

	manager::instance()->the_map.add_object(t);

	box_object* obj = new box_object;

	obj->dimens.x(5);
	obj->dimens.y(5);
	obj->dimens.w(5);
	obj->dimens.h(5);

	manager::instance()->the_map.add_object(obj);

	CHECK( t->think() == false );
	CHECK( t->think() == true );

	manager::destroy();
}

TEST_CASE( "trigger triggers on objects inside it", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->the_map.init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->dimens.x(0);
	t->dimens.y(0);
	t->dimens.w(100);
	t->dimens.h(100);

	manager::instance()->the_map.add_object(t);

	box_object* obj = new box_object;

	obj->dimens.x(5);
	obj->dimens.y(5);
	obj->dimens.w(5);
	obj->dimens.h(5);

	manager::instance()->the_map.add_object(obj);

	manager::instance()->the_map.think();

	CHECK( t->times_acted == 1 );

	manager::destroy();
}

TEST_CASE( "trigger doesn't trigger on objects not inside it", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->the_map.init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->dimens.x(0);
	t->dimens.y(0);
	t->dimens.w(100);
	t->dimens.h(100);

	manager::instance()->the_map.add_object(t);

	box_object* obj = new box_object;

	obj->dimens.x(200);
	obj->dimens.y(200);
	obj->dimens.w(5);
	obj->dimens.h(5);

	manager::instance()->the_map.add_object(obj);

	manager::instance()->the_map.think();

	CHECK( t->times_acted == 0 );

	manager::destroy();
}

TEST_CASE( "trigger triggers in intervals", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->the_map.init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->dimens.x(0);
	t->dimens.y(0);
	t->dimens.w(100);
	t->dimens.h(100);
	t->interval(2);

	manager::instance()->the_map.add_object(t);

	box_object* obj = new box_object;

	obj->dimens.x(5);
	obj->dimens.y(5);
	obj->dimens.w(5);
	obj->dimens.h(5);

	manager::instance()->the_map.add_object(obj);

	for ( unsigned i=0; i < 10; i++ )
	{
		manager::instance()->the_map.think();
	}

	CHECK( t->times_acted == 5 );

	manager::destroy();
}

TEST_CASE( "trigger triggers in intervals on multiple objects", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->the_map.init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->dimens.x(0);
	t->dimens.y(0);
	t->dimens.w(100);
	t->dimens.h(100);
	t->interval(2);

	manager::instance()->the_map.add_object(t);

	box_object* obj = new box_object;
	obj->dimens.x(5);
	obj->dimens.y(5);
	obj->dimens.w(5);
	obj->dimens.h(5);
	manager::instance()->the_map.add_object(obj);

	box_object* obj2 = new box_object;
	obj2->dimens.x(5);
	obj2->dimens.y(5);
	obj2->dimens.w(5);
	obj2->dimens.h(5);
	manager::instance()->the_map.add_object(obj2);

	for ( unsigned i=0; i < 10; i++ )
	{
		manager::instance()->the_map.think();
	}

	CHECK( t->times_acted == 10 );

	manager::destroy();
}
