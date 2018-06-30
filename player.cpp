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

	delayed_attack_bullet* dab2 = new delayed_attack_bullet;
	delayed_attack_box* dab = new delayed_attack_box;

	dab2->att.owner(this);
	dab2->load_data_from_file("spaceman_special_side.info");

	dab->att.owner(this);
	dab->load_data_from_file("spaceman_neutral_side.info");

	_am.set_right_attack(dab2);
	_am.set_right_special_attack(dab);
}

player::~player()
{
}

bool player::think_more()
{
	bool special_pressed = false;

	if ( _am.can_move() )
	{
		up_pressed      = keys::instance()->key_pressed(SDLK_w) && !keys::instance()->key_pressed(SDLK_s);
		down_pressed    = keys::instance()->key_pressed(SDLK_s) && !keys::instance()->key_pressed(SDLK_w);
		left_pressed    = keys::instance()->key_pressed(SDLK_a) && !keys::instance()->key_pressed(SDLK_d);
		right_pressed   = keys::instance()->key_pressed(SDLK_d) && !keys::instance()->key_pressed(SDLK_a);
		special_pressed = keys::instance()->key_pressed(SDLK_LSHIFT);
	}

	bool attacking = keys::instance()->key_pressed(SDLK_SPACE);
	
	_am.think(attacking, attack_dir(), special_pressed, speeds.v_speed() != 0);

	return creature::think_more();
}
