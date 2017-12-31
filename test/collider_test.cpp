#include "catch.h"
#include "../collider.h"
#include "../object.h"
#include "../manager.h"
#include "../teleporter.h"
#include "../vel_accel.h"

TEST_CASE( "collider::move_phys collides with stuff", "[collider]" )
{
	box_object* still = new box_object;

	still->dimens.x(100);
	still->dimens.y(100);
	still->dimens.w(20);
	still->dimens.h(20);

	box_object* moving = new box_object;

	moving->dimens.x(80);
	moving->dimens.y(80);
	moving->dimens.w(10);
	moving->dimens.h(10);

	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(still);
	manager::instance()->the_map.add_object(moving);

	move_phys(moving,20,20);

	CHECK( moving->dimens.x() == 90 );
	CHECK( moving->dimens.y() == 90 );
}

TEST_CASE( "collider::move_phys doesn't collide with stuff not in the way", "[collider]" )
{
	box_object* still = new box_object;

	still->dimens.x(200);
	still->dimens.y(200);
	still->dimens.w(20);
	still->dimens.h(20);

	box_object* moving = new box_object;

	moving->dimens.x(80);
	moving->dimens.y(80);
	moving->dimens.w(10);
	moving->dimens.h(10);

	manager::instance()->the_map.empty();
	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(still);
	manager::instance()->the_map.add_object(moving);

	move_phys(moving,20,20);

	CHECK( moving->dimens.x() == 100 );
	CHECK( moving->dimens.y() == 100 );
}

TEST_CASE( "collider::colliding() tells if colliding in direction", "[collider]" )
{
	box_object* still = new box_object;

	still->dimens.x(100);
	still->dimens.y(100);
	still->dimens.w(20);
	still->dimens.h(20);

	box_object* moving = new box_object;

	moving->dimens.x(100);
	moving->dimens.y(121);
	moving->dimens.w(20);
	moving->dimens.h(20);

	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(still);
	manager::instance()->the_map.add_object(moving);

	move_phys(moving,0,-1);

	CHECK( moving->dimens.y() == 120 );
	CHECK( colliding(moving,0) == true );

	teleport(moving,100,79);
	move_phys(moving,0,1);

	CHECK( moving->dimens.y() == 80 );
	CHECK( colliding(moving,2) == true );

	teleport(moving,79,100);
	move_phys(moving,1,0);

	CHECK( moving->dimens.x() == 80 );
	CHECK( colliding(moving,1) == true );

	teleport(moving,121,100);
	move_phys(moving,-1,0);

	CHECK( moving->dimens.x() == 120 );
	CHECK( colliding(moving,3) == true );
}

TEST_CASE( "collider::handle_speeds moves the collider", "[collider]" )
{
	box_object* test = new box_object;

	test->dimens.x(100);
	test->dimens.y(100);
	test->dimens.w(20);
	test->dimens.h(20);

	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(test);

	test->speeds.h_speed(5);
	test->speeds.v_speed(5);

	handle_speeds(test->speeds, test);

	CHECK( test->dimens.x() == 105 );
	CHECK( test->dimens.y() == 105 );
}

TEST_CASE( "collider::handle_speeds handles acceleration", "[collider]" )
{
	box_object* test = new box_object;

	test->dimens.x(100);
	test->dimens.y(100);
	test->dimens.w(20);
	test->dimens.h(20);

	manager::instance()->the_map.init(1000,1000);
	manager::instance()->the_map.add_object(test);

	test->speeds.h_accel(5);
	test->speeds.v_accel(5);

	handle_speeds(test->speeds, test);

	CHECK( test->speeds.h_speed() == 5 );
	CHECK( test->speeds.v_speed() == 5 );

	handle_speeds(test->speeds, test);

	CHECK( test->speeds.h_speed() == 10 );
	CHECK( test->speeds.v_speed() == 10 );
}
