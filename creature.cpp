#include "creature.h"
#include "collider.h"
#include "manager.h"
#include <fstream>

creature::creature()
	:up_pressed(false),
	 down_pressed(false),
	 left_pressed(false),
	 right_pressed(false),
	 _on_ground(false),
	 _colliding_left(false),
	 _colliding_right(false),
	 _crouch_height(0),
	 _orig_height(0),
	 _was_crouching(false)
{
}

creature::~creature()
{
}

bool creature::think_more()
{
	_on_ground       = colliding(this,2);
	_colliding_left  = colliding(this,3);
	_colliding_right = colliding(this,1);

	_ga.apply_gravity(speeds, on_ground());

	_lg.find_ledge(speeds, dimens, on_ground());

	if ( crouching() )
	{
		if ( !_was_crouching )
		{
			_orig_height = dimens.h();
			dimens.h(crouch_height());
			dimens.y(dimens.y() + _orig_height - crouch_height());
		}

		_was_crouching = true;
	}
	else if ( _was_crouching )
	{
		dimens.h(_orig_height);
		dimens.y(dimens.y() - _orig_height + crouch_height());
		_was_crouching = false;
	}

	if ( left_pressed )
	{
		if ( !crouching() )
		{
			m.move_left(speeds);
		}
		else
		{
			m.face_left();
		}
	}

	if ( right_pressed )
	{
		if ( !crouching() )
		{
			m.move_right(speeds);
		}
		else
		{
			m.face_right();
		}
	}

	if ( speeds.h_speed() != 0 && on_ground() && ( (!left_pressed && !right_pressed) || crouching() ) )
	{
		f.apply_friction(speeds);
	}

	short jump_vel = jump_handler.handle_jumping(on_ground() || _lg.hanging(), up_pressed);

	if ( jump_vel )
	{
		_lg.let_go();

		speeds.v_speed( jump_vel );
	}

	if ( (left_pressed && !colliding_left()) || (right_pressed && !colliding_right()) || down_pressed || up_pressed )
	{
		_lg.let_go();
	}

	anims.think( on_ground(), crouching(), m.facing_left(), (speeds.h_speed() != 0), _lg.hanging(), false );
	anims.draw(dimens);

	if ( attackable::think_more() )
	{
		return true;
	}

	return false;
}

bool creature::facing_left() const
{
	return m.facing_left();
}

bool creature::crouching() const
{
	return on_ground() && down_pressed && _crouch_height != 0;
}

bool creature::on_ground() const
{
	return _on_ground;
}

bool creature::colliding_left() const
{
	return _colliding_left;
}

bool creature::colliding_right() const
{
	return _colliding_right;
}

unsigned short creature::crouch_height() const
{
	return _crouch_height;
}

void creature::crouch_height(unsigned short height)
{
	_crouch_height = height;
}

unsigned short creature::attack_dir() const
{
	if ( up_pressed )
	{
		return 0;
	}
	else if ( down_pressed )
	{
		return 2;
	}
	else if ( left_pressed )
	{
		return 3;
	}
	else if ( right_pressed )
	{
		return 1;
	}

	return ( (facing_left()) ? 3 : 1 );
}

void creature::load_consts_from_file(std::string path)
{
	std::string full_path = manager::instance()->data_path() + "character-info/" + path;

	std::string buf;
	int tmp_i;
	double tmp_d;
	std::ifstream ifs(full_path);

	while ( ifs >> buf )
	{
		if ( buf == "hAccelRate" )
		{
			ifs >> tmp_d;
			m.h_accel_rate(tmp_d);
		}
		else if ( buf == "hSpeedMax" )
		{
			ifs >> tmp_d;
			m.h_speed_max(tmp_d);
		}
		else if ( buf == "jumpVel1" )
		{
			ifs >> tmp_d;
			jump_handler.jump_vel_1(tmp_d);
		}
		else if ( buf == "jumpVel2" )
		{
			ifs >> tmp_d;
			jump_handler.jump_vel_2(tmp_d);
		}
		else if ( buf == "friction" )
		{
			ifs >> tmp_d;
			f.coefficient(tmp_d);
		}
		else if ( buf == "width" )
		{
			ifs >> tmp_i;
			dimens.w(tmp_i);
		}
		else if ( buf == "height" )
		{
			ifs >> tmp_i;
			dimens.h(tmp_i);
		}
		else if ( buf == "crouchHeight" )
		{
			ifs >> tmp_i;
			crouch_height(tmp_i);
		}
		else
		{
			std::string msg = "invalid character-info for '" + full_path + "'";
			SDL_Log(msg.c_str());
			exit(1);
		}
	}
}
