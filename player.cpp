#include "player.h"
#include "manager.h"
#include "keys.h"

player::player()
{
	dimens.w(14);
	dimens.h(36);

	_running.load_data_from_file("spaceman_running.frames");
	_idle.load_data_from_file("spaceman_idle.frames");
	_jumping.load_data_from_file("spaceman_jumping.frames");
	_hanging.load_data_from_file("spaceman_hanging.frames");
	_punching.load_data_from_file("spaceman_punching.frames");

	anims.set_running_anim(_running);
	anims.set_disabled_anim(_running);
	anims.set_jumping_anim(_jumping);
	anims.set_hanging_anim(_hanging);
	anims.set_idle_anim(_idle);

	load_consts_from_file("spaceman.info");

	delayed_attack_bullet dab2 = new delayed_attack_bullet;
	delayed_attack_box dab = new delayed_attack_box;

	dab2.t.owner(this);
	dab2.t.knockback(5);

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
