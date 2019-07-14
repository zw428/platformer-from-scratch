#include "enemy_basic.h"

enemy_basic::enemy_basic()
{
	anim idle;
	anim running;
	anim jumping;
	anim hanging;
	anim punching;
	anim crouching;
	anim shooting;
	
	type(attackable_health);
	health(3);

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
}

enemy_basic::~enemy_basic()
{
}

bool enemy_basic::think_more()
{
	return creature::think_more();
}
