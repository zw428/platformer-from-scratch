#include "npc.h"
#include "manager.h"
#include "teleporter.h"
#include "collider.h"

npc::npc()
{
	type(attackable_knockback_multiplier);
	_img.texture(manager::instance()->resources.textures("test"));
	_img.w(dimens.w());
	_img.h(dimens.h());
}

npc::~npc()
{
}

bool npc::think()
{
	if ( box_object::think() )
	{
		return true;
	}

	bool on_ground = colliding(this, 2);

	_ga.apply_gravity(speeds, on_ground);

	if ( on_ground )
	{
		_f.apply_friction(speeds);
	}

	_img.x(dimens.x());
	_img.y(dimens.y());
	_img.draw();

	return false;
}
