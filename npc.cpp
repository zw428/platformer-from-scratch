#include "npc.h"
#include "manager.h"

npc::npc()
{
	_blank.texture(manager::instance()->resources.textures("test"));
	anims.set_running_anim(_blank);
	anims.set_disabled_anim(_blank);
	anims.set_jumping_anim(_blank);
	anims.set_hanging_anim(_blank);
	anims.set_idle_anim(_blank);
}

npc::~npc()
{
}
