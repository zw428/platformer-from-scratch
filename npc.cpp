#include "npc.h"

#include "manager.h"
#include "collide_functions.h"
#include "player.h"

npc::npc()
	 :knockback_mult(),
	  _x_dest(0),
	  _y_dest(0)
{
	set_collision_object( dynamic_cast<object*>(this) );
	health(10);

	_img.texture(manager::instance()->textures("test"));
	_img.w(w());
	_img.h(h());
}

bool npc::think()
{
	handle_speeds();
	handle_gravity();

	static unsigned short think_delay = 0;

	if ( x() != _x_dest)
	{
		if ( _x_dest < x() )
		{
			move_left();
		}
		else
		{
			move_right();
		}
	}

	if ( think_delay == 0 )
	{
		std::vector<object*> objs = manager::instance()->get_map()->objects_considered( dynamic_cast<object*>(this) );

		think_delay = 10;

		for ( unsigned i=0; i < objs.size(); i++ )
		{
			player* pl = dynamic_cast<player*>(objs[i]);
			if ( pl )
			{
				unsigned short player_x = pl->x();
				unsigned short player_y = pl->y();
				dest(player_x, player_y);

				break;
			}
		}
	}
	else
	{
		think_delay--;
	}

	if ( health() == 0 )
	{
		return true;
	}

	_img.x(x());
	_img.y(y());
	_img.draw();

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
