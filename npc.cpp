#include "npc.h"
#include "manager.h"
#include "alive.h"

npc::npc()
	 :knockback_mult(),
	  object(),
	  death()
{
	set_collision_object( dynamic_cast<object*>(this) );

	_img.texture(manager::instance()->textures("test"));
	_img.w(w());
	_img.h(h());
}

npc::~npc()
{
}

bool npc::think()
{
	handle_speeds();
	handle_gravity();
	handle_disabled();

	if ( colliding(2) )
	{
		apply_friction();
	}

	_img.x(x());
	_img.y(y());
	_img.draw();

	return false;
}

bool npc::on_death()
{
	teleport(500,300);

	return false;
}
