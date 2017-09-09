#include "catch.hpp"
#include "../collider.h"
#include "../object.h"
#include "../manager.h"

class collider_tmp : public object
{
public:
	collider_tmp() :object() {};
	bool think() { return false; };
};

TEST_CASE( "collider constructors initialize things", "[collider]" )
{
	SECTION( "collider()" )
	{
		collider c;
		CHECK( c.collision_object() == 0 );
	}

	SECTION( "collider( object* obj )" )
	{
		collider_tmp t;
		collider c( dynamic_cast<object*>(&t) );
		CHECK( c.collision_object() == &t );
	}
}

TEST_CASE( "collider::move_phys collides with stuff", "[collider]" )
{
	collider_tmp* still = new collider_tmp;

	still->x(100);
	still->y(100);
	still->w(20);
	still->h(20);

	collider_tmp* moving = new collider_tmp;

	moving->x(80);
	moving->y(80);
	moving->w(10);
	moving->h(10);

	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(still);
	manager::instance()->get_map()->add_object(moving);

	moving->move_phys(20,20);

	CHECK( moving->x() == 90 );
	CHECK( moving->y() == 90 );
}

TEST_CASE( "collider::move_phys doesn't collide with stuff not in the way", "[collider]" )
{
	collider_tmp* still = new collider_tmp;

	still->x(200);
	still->y(200);
	still->w(20);
	still->h(20);

	collider_tmp* moving = new collider_tmp;

	moving->x(80);
	moving->y(80);
	moving->w(10);
	moving->h(10);

	manager::instance()->get_map()->empty();
	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(still);
	manager::instance()->get_map()->add_object(moving);

	moving->move_phys(20,20);

	CHECK( moving->x() == 100 );
	CHECK( moving->y() == 100 );
}

TEST_CASE( "collider::colliding() tells if colliding in direction", "[collider]" )
{
	collider_tmp* still = new collider_tmp;

	still->x(100);
	still->y(100);
	still->w(20);
	still->h(20);

	collider_tmp* moving = new collider_tmp;

	moving->x(100);
	moving->y(121);
	moving->w(20);
	moving->h(20);

	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(still);
	manager::instance()->get_map()->add_object(moving);

	moving->move_phys(0,-1);

	CHECK( moving->y() == 120 );
	CHECK( moving->colliding(0) == true );

	moving->teleport(100,79);
	moving->move_phys(0,1);

	CHECK( moving->y() == 80 );
	CHECK( moving->colliding(2) == true );

	moving->teleport(79,100);
	moving->move_phys(1,0);

	CHECK( moving->x() == 80 );
	CHECK( moving->colliding(1) == true );

	moving->teleport(121,100);
	moving->move_phys(-1,0);

	CHECK( moving->x() == 120 );
	CHECK( moving->colliding(3) == true );
}

TEST_CASE( "collider::set_collision_object works", "[collider]" )
{
	collider_tmp t;

	object* obj;

	t.set_collision_object(obj);

	CHECK( t.collision_object() == obj );
}

TEST_CASE( "collider::handle_speeds moves the collider", "[collider]" )
{
	collider_tmp* test = new collider_tmp;

	test->x(100);
	test->y(100);
	test->w(20);
	test->h(20);

	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(test);

	test->h_speed(5);
	test->v_speed(5);

	test->handle_speeds();

	CHECK( test->x() == 105 );
	CHECK( test->y() == 105 );
}

TEST_CASE( "collider::handle_speeds handles acceleration", "[collider]" )
{
	collider_tmp* test = new collider_tmp;

	test->x(100);
	test->y(100);
	test->w(20);
	test->h(20);

	manager::instance()->get_map()->init(1000,1000);
	manager::instance()->get_map()->add_object(test);

	test->h_accel(5);
	test->v_accel(5);

	test->handle_speeds();

	CHECK( test->h_speed() == 5 );
	CHECK( test->v_speed() == 5 );

	test->handle_speeds();

	CHECK( test->h_speed() == 10 );
	CHECK( test->v_speed() == 10 );
}
