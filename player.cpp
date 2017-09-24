#include "player.h"
#include "manager.h"
#include "keys.h"
#include "attackable.h"
#include "attack_box.h"
#include "collider.h"
#include "directed_attack.h"
#include <cmath>

player::player()
	 :alive(),
	  object()
{
	weightless(false);

	_attack_delay = 30;
	_attack_counter = _attack_delay;

	_anm.texture(manager::instance()->textures("sheet"));
	_anm.w(w());
	_anm.h(h());
	_anm.clip_width(100);
	_anm.frame_dur(3);
	h_accel_rate(0.5);
}

player::~player()
{
}

bool player::think()
{
	bool on_ground       = colliding(this,2);
	bool colliding_left  = colliding(this,3);
	bool colliding_right = colliding(this,1);

	bool up        = keys::instance()->key_pressed(SDLK_w) && !keys::instance()->key_pressed(SDLK_s);
	bool down      = keys::instance()->key_pressed(SDLK_s) && !keys::instance()->key_pressed(SDLK_w);
	bool left      = keys::instance()->key_pressed(SDLK_a) && !keys::instance()->key_pressed(SDLK_d);
	bool right     = keys::instance()->key_pressed(SDLK_d) && !keys::instance()->key_pressed(SDLK_a);
	bool attacking = keys::instance()->key_pressed(SDLK_SPACE);

	if ( _attack_counter > 0 )
	{
		_attack_counter--;
	}

	if ( v_speed() > 0 && !on_ground )
	{
		find_ledge(this);

		if ( found_ledge() )
		{
			if ( v_speed() > dist_to_ledge() )
			{
				v_speed( dist_to_ledge() );
			}

			if ( v_speed() == 0 )
			{
				on_ground = true;

				if ( h_dist_to_ledge() > 0 )
				{
					h_speed(4);
					move_right(0);
				}
				else if ( h_dist_to_ledge() < 0 )
				{
					h_speed(-4);
					move_left(0);
				}
			}
		}
	}

	if ( left )
	{
		if ( !colliding_left )
		{
			let_go();
			h_speed(move_left(h_speed()));
		}
		else if ( v_speed() > 0 )
		{
			v_speed(v_speed() - friction_reduction( v_speed()));
		}

		_anm.flip_h(facing_left());
	}
	else if ( right )
	{
		if ( !colliding_right )
		{
			let_go();
			h_speed(move_right(h_speed()));
		}
		else if ( v_speed() > 0 )
		{
			v_speed(v_speed() - friction_reduction( v_speed()));
		}

		_anm.flip_h(facing_left());
	}
	else if ( on_ground )
	{
		h_speed(h_speed() - friction_reduction( h_speed()));
	}

	if ( down )
	{
		let_go();
	}

	if ( !on_ground )
	{
		v_accel( gravity_accel(on_ground) );
	}

	short jump_vel = handle_jumping(on_ground, up);

	if ( jump_vel )
	{
		v_speed( jump_vel );
	}

	if ( attacking && _attack_counter == 0 )
	{
		start_attack();
	}

	handle_speeds(this);

	_anm.x(x());
	_anm.y(y());
	_anm.draw();

	return false;
}

void player::start_attack()
{
	attack att;
	att.sound("test");
	att.damage(10);
	att.knockback(5);
	att.owner( this );

	directed_attack da;

	if ( facing_left() )
	{
		da.attack_left( att, this, 20, h() );
	}
	else if ( facing_right() )
	{
		da.attack_right( att, this, 20, h() );
	}

	_attack_counter = _attack_delay;
}
