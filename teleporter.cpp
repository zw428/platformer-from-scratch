#include "teleporter.h"
#include "manager.h"
#include "object.h"
#include "collide_functions.h"

teleporter::teleporter()
{
}

bool teleporter::teleport( int x, int y )
{
	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( dynamic_cast<object*>( collision_object() ) );

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		const object* obj = objects_vec.at(i);

		if ( box_in_box( x, y, w(), h(), obj->x(), obj->y(), obj->w(), obj->h() ) )
		{
			return false;
		}
	}

	box::x(x);
	box::y(y);

	return true;
}
