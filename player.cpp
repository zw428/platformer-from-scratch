#include "player.h"
#include "manager.h"
#include "keys.h"

player::player()
{
	_running.texture(manager::instance()->resources.textures("spaceman_running"));
	_running.clip_width(12);
	_running.w(12);
	_running.h(34);

	dimens.w(14);
	dimens.h(36);

	for ( unsigned i=0; i < 6; i++ )
	{
		_running.add_frame_dur(5);
	}

	_idle.texture(manager::instance()->resources.textures("spaceman_standing"));
	_idle.clip_width(15);
	_idle.w(15);
	_idle.h(36);
	_idle.add_frame_dur(90);
	_idle.add_frame_dur(5);
	_idle.add_frame_dur(85);
	_idle.add_frame_dur(4);

	_jumping.texture(manager::instance()->resources.textures("spaceman_jumping"));
	_jumping.w(15);
	_jumping.h(33);

	_hanging.texture(manager::instance()->resources.textures("spaceman_hanging"));
	_hanging.w(15);
	_hanging.h(33);

	_punching.texture(manager::instance()->resources.textures("spaceman_punching"));
	_punching.w(12);
	_punching.clip_width(12);
	_punching.h(33);
	_punching.add_frame_dur(3);
	_punching.add_frame_dur(12);
	_punching.add_frame_dur(4);
	_punching.add_frame_dur(18);

	m.h_accel_rate(0.2);
	m.h_speed_max(2);
	jump_handler.jump_vel_1(6);
	jump_handler.jump_vel_2(6);

	anims.set_running_anim(_running);
	anims.set_disabled_anim(_running);
	anims.set_jumping_anim(_jumping);
	anims.set_hanging_anim(_hanging);
	anims.set_idle_anim(_idle);

	delayed_attack_bullet* dab2 = new delayed_attack_bullet;
	delayed_attack_box* dab = new delayed_attack_box;

	dab2->att.owner(this);
	dab2->att.knockback(5);

	dab->att.owner(this);
	dab->att.hit_angle(-90);
	dab->offset.x(dimens.w());
	dab->att.sound("test");
	dab->att.damage(10);
	dab->att.knockback(10);
	dab->offset.x(dimens.w());
	dab->dimens.h(36);
	dab->add_as_child = true;

	_am.set_up_attack(dab2);
	_am.set_up_air_attack(dab);
}

player::~player()
{
}

bool player::think_more()
{
	if ( _am.can_move() )
	{
		up_pressed        = keys::instance()->key_pressed(SDLK_w) && !keys::instance()->key_pressed(SDLK_s);
		down_pressed      = keys::instance()->key_pressed(SDLK_s) && !keys::instance()->key_pressed(SDLK_w);
		left_pressed      = keys::instance()->key_pressed(SDLK_a) && !keys::instance()->key_pressed(SDLK_d);
		right_pressed     = keys::instance()->key_pressed(SDLK_d) && !keys::instance()->key_pressed(SDLK_a);
	}

	bool attacking = keys::instance()->key_pressed(SDLK_SPACE);
	
	_am.think(attacking, 0, false, speeds.v_speed() != 0);

	return creature::think_more();
}
