#include "catch.hpp"
#include "../trigger.h"
#include "../object.h"
#include "../manager.h"

class trigger_tmp : public trigger
{
public:
	bool action( object* obj ) { times_acted++; return false; };
	int times_acted = 0;
};

class trigger_tmp2 : public object
{
public:
	bool think() { return false; };
};

TEST_CASE( "trigger initializes stuff", "[trigger]" )
{
	trigger_tmp t;

	CHECK( t.interval() == 30 );
	CHECK( t.lifespan() == 0 );
}

TEST_CASE( "trigger setters/getters work", "[trigger]" )
{
	trigger_tmp t;

	t.lifespan(5);
	t.interval(6);

	CHECK( t.lifespan() == 5);
	CHECK( t.interval() == 6);
}

TEST_CASE( "trigger dies (returns true) when lifespan is over", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->get_map()->init(1024,1024);

	trigger_tmp t;
	t.lifespan(5);

	for ( unsigned i=0; i < 5; i++ )
	{
		t.think();
	}

	CHECK( t.think() == true );

	manager::destroy();
}

TEST_CASE( "trigger triggers on objects inside it", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->get_map()->init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->x(0);
	t->y(0);
	t->w(100);
	t->h(100);

	manager::instance()->get_map()->add_trigger(t);

	trigger_tmp2* obj = new trigger_tmp2;

	obj->x(5);
	obj->y(5);
	obj->w(5);
	obj->h(5);

	manager::instance()->get_map()->add_object(obj);

	manager::instance()->get_map()->think();

	CHECK( t->times_acted == 1 );

	manager::destroy();
}

TEST_CASE( "trigger doesn't trigger on objects not inside it", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->get_map()->init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->x(0);
	t->y(0);
	t->w(100);
	t->h(100);

	manager::instance()->get_map()->add_trigger(t);

	trigger_tmp2* obj = new trigger_tmp2;

	obj->x(200);
	obj->y(200);
	obj->w(5);
	obj->h(5);

	manager::instance()->get_map()->add_object(obj);

	manager::instance()->get_map()->think();

	CHECK( t->times_acted == 0 );

	manager::destroy();
}

TEST_CASE( "trigger triggers in intervals", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->get_map()->init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->x(0);
	t->y(0);
	t->w(100);
	t->h(100);
	t->interval(2);

	manager::instance()->get_map()->add_trigger(t);

	trigger_tmp2* obj = new trigger_tmp2;

	obj->x(5);
	obj->y(5);
	obj->w(5);
	obj->h(5);

	manager::instance()->get_map()->add_object(obj);

	for ( unsigned i=0; i < 10; i++ )
	{
		manager::instance()->get_map()->think();
	}

	CHECK( t->times_acted == 5 );

	manager::destroy();
}

TEST_CASE( "trigger triggers in intervals on multiple objects", "[trigger]" )
{
	manager::instance()->init(true);
	manager::instance()->get_map()->init(1024,1024);

	trigger_tmp* t = new trigger_tmp;
	t->x(0);
	t->y(0);
	t->w(100);
	t->h(100);
	t->interval(2);

	manager::instance()->get_map()->add_trigger(t);

	trigger_tmp2* obj = new trigger_tmp2;
	obj->x(5);
	obj->y(5);
	obj->w(5);
	obj->h(5);
	manager::instance()->get_map()->add_object(obj);

	trigger_tmp2* obj2 = new trigger_tmp2;
	obj2->x(5);
	obj2->y(5);
	obj2->w(5);
	obj2->h(5);
	manager::instance()->get_map()->add_object(obj2);

	for ( unsigned i=0; i < 10; i++ )
	{
		manager::instance()->get_map()->think();
	}

	CHECK( t->times_acted == 10 );

	manager::destroy();
}
