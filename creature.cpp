#include "creature.h"
#include "collider.h"
#include "manager.h"
#include <fstream>

creature::creature()
	:up_pressed(false),
	 down_pressed(false),
	 left_pressed(false),
	 right_pressed(false),
	 _facing_left(false)
{
}

creature::~creature()
{
}

bool creature::think_more()
{
	bool on_ground       = colliding(this,2);
	bool colliding_left  = colliding(this,3);
	bool colliding_right = colliding(this,1);

	_ga.apply_gravity(speeds, on_ground);

	_lg.find_ledge(speeds, dimens, on_ground);

	if ( left_pressed && !right_pressed )
	{
		m.move_left(speeds);
		_facing_left = true;
	}

	if ( right_pressed && !left_pressed )
	{
		m.move_right(speeds);
		_facing_left = false;
	}

	if ( speeds.h_speed() != 0 && on_ground && !left_pressed && !right_pressed )
	{
		f.apply_friction(speeds);
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

	if ( attackable::think_more() )
	{
		return true;
	}

	return false;
}

bool creature::facing_left() const
{
	return _facing_left;
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
	double tmp_d;
	std::ifstream ifs(full_path);

	while ( ifs >> buf )
	{
		if ( buf == "h_accel_rate" )
		{
			ifs >> tmp_d;
			m.h_accel_rate(tmp_d);
		}
		else if ( buf == "h_speed_max" )
		{
			ifs >> tmp_d;
			m.h_speed_max(tmp_d);
		}
		else if ( buf == "jump_vel_1" )
		{
			ifs >> tmp_d;
			jump_handler.jump_vel_1(tmp_d);
		}
		else if ( buf == "jump_vel_2" )
		{
			ifs >> tmp_d;
			jump_handler.jump_vel_2(tmp_d);
		}
		else if ( buf == "friction" )
		{
			ifs >> tmp_d;
			f.coefficient(tmp_d);
		}
		else
		{
			std::string msg = "invalid character-info for '" + full_path + "'";
			SDL_Log(msg.c_str());
			exit(1);
		}
	}
}
