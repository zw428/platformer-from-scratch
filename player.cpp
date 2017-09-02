#include "player.h"

#include "manager.h"
#include "keys.h"
#include <cmath>

player::player()
	 :alive()
{
	weightless(false);
	set_collision_object( dynamic_cast<object*>(this) );

	_attack_delay = 30;

	_anm.texture(manager::instance()->textures("sheet"));
	_anm.w(w());
	_anm.h(h());
	_anm.clip_width(100);
	_anm.frame_dur(1);
}

bool player::think()
{
	handle_speeds();
	handle_gravity();

	if ( _attack_counter > 0 )
	{
		_attack_counter--;
	}

	short x_add = 0;
	short y_add = 0;

	const short speed = 10;

	bool up        = keys::instance()->key_pressed(SDLK_w) && !keys::instance()->key_pressed(SDLK_s);
	bool down      = keys::instance()->key_pressed(SDLK_s) && !keys::instance()->key_pressed(SDLK_w);
	bool left      = keys::instance()->key_pressed(SDLK_a) && !keys::instance()->key_pressed(SDLK_d);
	bool right     = keys::instance()->key_pressed(SDLK_d) && !keys::instance()->key_pressed(SDLK_a);
	bool attacking = keys::instance()->key_pressed(SDLK_SPACE);

	if ( up && colliding(2) )
	{
		v_speed(-10);
	}

	if ( down )
	{
		//nothing
	}

	if ( left )
	{
		x_add = -speed;
	}

	if ( right )
	{
		x_add = speed;
	}

	if ( !move_phys(x_add,y_add) )
	{
		if ( !move_phys(0,y_add ) )
		{
			move_phys(x_add,0);
		}

	}

	if ( attacking && _attack_counter == 0 )
	{
		start_attack();
	}

	_anm.x(x());
	_anm.y(y());
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
	b->owner(this);

	b->y( y() );
	b->h( h() );

	b->x( x() + w() );
	b->w( 100 );

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
