#include "teleporter.h"
#include "manager.h"
#include "object.h"
#include "collide_functions.h"

bool teleport( object* obj, int x, int y )
{
	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( obj );

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		const object* other_obj = objects_vec.at(i);

		if ( box_in_box( x, y, obj->w(), obj->h(), other_obj->x(), other_obj->y(), other_obj->w(), other_obj->h() ) )
		{
			return false;
		}
	}

	obj->x(x);
	obj->y(y);

	return true;
}
