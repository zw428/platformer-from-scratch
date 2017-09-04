#include "npc.h"

#include "manager.h"
#include "collide_functions.h"
#include "player.h"

npc::npc()
	 :knockback_mult(),
	  object(),
	  death(),
	  _x_dest(0),
	  _y_dest(0)
{
	set_collision_object( dynamic_cast<object*>(this) );
	health(10);

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

	if ( health() == 0 )
	{
		return on_death();
	}

	_img.x(x());
	_img.y(y());
	_img.draw();

	return false;
}

bool npc::on_death()
{
	health(10);
	teleport(500,300);

	return false;
}

void npc::dest( unsigned short x, unsigned short y )
{
	_x_dest = x;
	_y_dest = y;
}

bool npc::can_move()
{
	return _can_move;
}
