#include "bullet.h"
#include <cmath>
#include <vector>
#include "manager.h"
#include "collide_functions.h"
#include "attackable.h"
#include "block.h"

bullet::bullet()
	:_speed(5), _theta(0)
{
	w(5);
	h(5);
	sound("test");
}

bool bullet::think()
{
	x( x() + _speed*std::cos( _theta * M_PI / 180 ) );
	y( y() + _speed*std::sin( _theta * M_PI / 180 ) );

	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( this );

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		if ( box_in_box( this, objects_vec[i] ) )
		{
			attackable* a = dynamic_cast<attackable*>(objects_vec[i]);

			if ( a && a != owner() )
			{
				perform( a, this );
				return true;
			}

			block* b = dynamic_cast<block*>(objects_vec[i]);

			if ( b )
			{
				return true;
			}
		}
	}

	draw();

	return false;
}
