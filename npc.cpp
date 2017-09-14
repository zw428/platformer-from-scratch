#include "npc.h"
#include "manager.h"
#include "alive.h"
#include "teleporter.h"

npc::npc()
	 :knockback_mult(),
	  object(),
	  death()
{
	_img.texture(manager::instance()->textures("test"));
	_img.w(w());
	_img.h(h());
}

npc::~npc()
{
}

bool npc::think()
{
	handle_speeds(this);
	handle_disabled();

	bool on_ground = colliding(this,2);

	if ( on_ground )
	{
		apply_friction();
	}
	else
	{
		v_accel( gravity_accel(false) );
	}

	_img.x(x());
	_img.y(y());
	_img.draw();

	return false;
}

bool npc::on_death()
{
	teleport(this,500,300);

	return false;
}
