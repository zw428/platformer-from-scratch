#include "player.h"
#include "manager.h"
#include "keys.h"
#include "attackable.h"
#include "attack_box.h"
#include "collider.h"
#include "directed_attack.h"
#include "bullet.h"

player::player()
	 :alive(),
	  object()
{
	_running.texture(manager::instance()->textures("spaceman_running"));
	_running.clip_width(12);
	_running.w(12);
	_running.h(34);

	w(14);
	h(36);

	for ( unsigned i=0; i < 6; i++ )
	{
		_running.add_frame_dur(5);
	}

	_idle.texture(manager::instance()->textures("spaceman_standing"));
	_idle.clip_width(15);
	_idle.w(15);
	_idle.h(36);
	_idle.add_frame_dur(90);
	_idle.add_frame_dur(5);
	_idle.add_frame_dur(85);
	_idle.add_frame_dur(4);

	_jumping.texture(manager::instance()->textures("spaceman_jumping"));
	_jumping.w(15);
	_jumping.h(33);

	_hanging.texture(manager::instance()->textures("spaceman_hanging"));
	_hanging.w(15);
	_hanging.h(33);

	_punching.texture(manager::instance()->textures("spaceman_punching"));
	_punching.w(12);
	_punching.clip_width(12);
	_punching.h(33);
	_punching.add_frame_dur(3);
	_punching.add_frame_dur(12);
	_punching.add_frame_dur(4);
	_punching.add_frame_dur(18);
	_attack1.delay(19);

	_am.set_running_anim(_running);
	_am.set_disabled_anim(_running);
	_am.set_jumping_anim(_jumping);
	_am.set_hanging_anim(_hanging);
	_am.set_idle_anim(_idle);

	_m.h_accel_rate(0.2);
	_m.h_speed_max(2);
	_jumper.jump_vel_1(6);
	_jumper.jump_vel_2(6);
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

	if ( attacking && !_attack1.cooling_down() )
	{
		_am.set_override_anim(&_punching);
	}

	_attack1.think(attacking);

	if ( _attack1.ready() )
	{
		shoot();
	}

	_ga.apply_gravity(this, on_ground);

	_lg.find_ledge(this, on_ground);

	if ( left )
	{
		_m.move_left(this, h_speed());
	}

	if ( right )
	{
		_m.move_right(this, h_speed());
	}

	if ( h_speed() != 0 && on_ground && !left && !right )
	{
		_f.apply_friction(this);
	}

	short jump_vel = _jumper.handle_jumping(on_ground || _lg.hanging(), up);

	if ( jump_vel )
	{
		_lg.let_go();

		v_speed( jump_vel );
	}

	if ( (left && !colliding_left) || (right && !colliding_right) || down || up )
	{
		_lg.let_go();
	}

	handle_speeds(this);
	_am.think( on_ground, _m.facing_left(), (h_speed() != 0), _lg.hanging(), false );
	_am.draw(this);

	return false;
}

void player::punch()
{
	attack att;
	att.sound("test");
	att.damage(10);
	att.knockback(5);
	att.owner( this );

	directed_attack da;

	if ( _m.facing_left() )
	{
		da.attack_left( att, this, 5, h() );
	}
	else
	{
		da.attack_right( att, this, 5, h() );
	}
}

void player::shoot()
{
	bullet* b = new bullet();
	b->texture( manager::instance()->textures("test") );

	attack a;
	a.sound("test");
	a.damage(10);
	a.knockback(5);
	a.owner( this );

	b->set_attack(a);

	b->x(x());
	b->y(y_center());

	if ( _m.facing_left() )
	{
		b->reverse();
		b->x( b->x() - b->w());
	}
	else
	{
		b->x( b->x() + w());
	}

	manager::instance()->get_map()->add_object(b);
}
