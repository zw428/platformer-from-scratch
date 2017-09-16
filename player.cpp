#include "player.h"
#include "manager.h"
#include "keys.h"
#include "attackable.h"
#include "attack_box.h"
#include "collider.h"
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
}

player::~player()
{
}

bool player::think()
{
	handle_speeds(this);

	bool on_ground = colliding(this,2);

	if ( _attack_counter > 0 )
	{
		_attack_counter--;
	}

	bool up        = keys::instance()->key_pressed(SDLK_w) && !keys::instance()->key_pressed(SDLK_s);
	bool down      = keys::instance()->key_pressed(SDLK_s) && !keys::instance()->key_pressed(SDLK_w);
	bool left      = keys::instance()->key_pressed(SDLK_a) && !keys::instance()->key_pressed(SDLK_d);
	bool right     = keys::instance()->key_pressed(SDLK_d) && !keys::instance()->key_pressed(SDLK_a);
	bool attacking = keys::instance()->key_pressed(SDLK_SPACE);

	short jump_vel = handle_jumping(on_ground, up);

	if ( jump_vel )
	{
		v_speed( jump_vel );
	}

	if ( down )
	{
		//nothing
	}

	if ( left )
	{
		h_speed(move_left(h_speed()));
	}
	else if ( right )
	{
		h_speed(move_right(h_speed()));
	}
	else if ( on_ground )
	{
		h_speed(h_speed() - friction_reduction( h_speed()));
	}

	if ( !on_ground )
	{
		v_accel( gravity_accel(on_ground) );
	}

	if ( attacking && _attack_counter == 0 )
	{
		start_attack();
	}

	_anm.x(x());
	_anm.y(y());
	_anm.flip_h(facing_left());
	_anm.draw();

	return false;
}

void player::start_attack()
{
	_attack_counter = _attack_delay;
	attack_box* b = new attack_box();
	b->sound("test");
	b->damage(5);
	b->knockback(20);
	b->owner( dynamic_cast<attackable*>(this));

	b->y( y() );
	b->h( h() );

	b->x( x() + w() );
	b->w( 3 );

	trigger* tr = dynamic_cast<trigger*>(b);

	if ( tr )
	{
		manager::instance()->get_map()->add_trigger( tr );
	}
	else
	{
		delete tr;
	}
}
