#include "player.h"
#include "manager.h"
#include "keys.h"
#include <fstream>

player::player()
{
	anim idle;
	anim running;
	anim jumping;
	anim hanging;
	anim punching;
	anim crouching;
	anim shooting;

	running.load_data_from_file("spaceman_running.frames");
	idle.load_data_from_file("spaceman_idle.frames");
	jumping.load_data_from_file("spaceman_jumping.frames");
	hanging.load_data_from_file("spaceman_hanging.frames");
	crouching.load_data_from_file("spaceman_crouching.frames");
	punching.load_data_from_file("spaceman_punching.frames");
	shooting.load_data_from_file("spaceman_shooting.frames");
	crouching.load_data_from_file("spaceman_crouching.frames");

	anims.set_running_anim(running);
	anims.set_disabled_anim(running);
	anims.set_jumping_anim(jumping);
	anims.set_hanging_anim(hanging);
	anims.set_crouching_anim(crouching);
	anims.set_idle_anim(idle);

	load_consts_from_file("spaceman.info");

	delayed_attack_bullet* dab2 = new delayed_attack_bullet;
	delayed_attack_box* dab = new delayed_attack_box;

	dab2->att.owner(this);
	dab2->load_data_from_file("spaceman_special_side.info");

	dab->att.owner(this);
	dab->load_data_from_file("spaceman_neutral_side.info");

	_am.set_right_attack(dab, punching);
	_am.set_right_special_attack(dab2, shooting);
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
	
	_am.think(anims, attacking, attack_dir(), special_pressed, !on_ground(), crouching());

	return creature::think_more();
}

void load_data_from_file()
{
}