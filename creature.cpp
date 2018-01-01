#include "creature.h"
#include "collider.h"

creature::creature()
	:up_pressed(false),
	 down_pressed(false),
	 left_pressed(false),
	 right_pressed(false)
{
}

creature::~creature()
{
}

bool creature::think()
{
	bool on_ground       = colliding(this,2);
	bool colliding_left  = colliding(this,3);
	bool colliding_right = colliding(this,1);

	_ga.apply_gravity(speeds, on_ground);

	_lg.find_ledge(speeds, dimens, on_ground);

	if ( left_pressed )
	{
		m.move_left(speeds);
	}

	if ( right_pressed )
	{
		m.move_right(speeds);
	}

	if ( speeds.h_speed() != 0 && on_ground && !left_pressed && !right_pressed )
	{
		_f.apply_friction(speeds);
	}

	short jump_vel = jump_handler.handle_jumping(on_ground || _lg.hanging(), up_pressed);

	if ( jump_vel )
	{
		_lg.let_go();

		speeds.v_speed( jump_vel );
	}

	if ( (left_pressed && !colliding_left) || (right_pressed && !colliding_right) || down_pressed || up_pressed )
	{
		_lg.let_go();
	}

	anims.think( on_ground, m.facing_left(), (speeds.h_speed() != 0), _lg.hanging(), false );
	anims.draw(dimens);

	if ( attackable::think() )
	{
		return true;
	}

	return false;
}
