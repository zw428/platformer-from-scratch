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

	anim running;

	running.texture(manager::instance()->textures("spaceman_running"));
	running.clip_width(12);
	running.w(12);
	running.h(34);

	w(14);
	h(36);

	for ( unsigned i=0; i < 6; i++ )
	{
		running.add_frame_dur(5);
	}

	anim idle;
	idle.texture(manager::instance()->textures("spaceman_standing"));
	idle.clip_width(15);
	idle.w(15);
	idle.h(36);
	idle.add_frame_dur(90);
	idle.add_frame_dur(5);
	idle.add_frame_dur(85);
	idle.add_frame_dur(4);

	_am.set_running_anim(running);
	_am.set_disabled_anim(running);
	_am.set_jumping_anim(running);
	_am.set_idle_anim(idle);

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

	_attack1.think(attacking);
	_am.think( on_ground, facing_left(), (h_speed() != 0), false );

	if ( _attack1.ready() )
	{
		start_attack();
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
	}
	else if ( on_ground )
	{
		h_speed(h_speed() - friction_reduction( h_speed()));
	}

	if ( down )
	{
		let_go();
	}

	v_accel( gravity_accel(on_ground) );

	short jump_vel = handle_jumping(on_ground, up);

	if ( jump_vel )
	{
		v_speed( jump_vel );
	}

	handle_speeds(this);
	_am.draw(this);

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
}
