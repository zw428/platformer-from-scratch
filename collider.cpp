#include "collider.h"
#include "manager.h"
#include "object.h"
#include "vel_accel.h"
#include "collide_functions.h"

bool move_phys( object* obj, short x_add, short y_add )
{
	if ( x_add == 0 && y_add == 0 )
	{
		return false;
	}

	int map_size_x = manager::instance()->get_map()->x_size();
	int map_size_y = manager::instance()->get_map()->y_size();

	if ( int(obj->x()) + x_add < 0 )
	{
		x_add = -obj->x();
	}

	if ( int(obj->x()) + x_add + obj->w() > map_size_x )
	{
		x_add = map_size_x - obj->x() - obj->w();
	}

	if ( int(obj->y()) + y_add < 0 )
	{
		y_add = -obj->y();
	}

	if ( int(obj->y()) + y_add + obj->h() > map_size_y )
	{
		y_add = map_size_y - obj->y() - obj->h();
	}

	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( obj );

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		const object* other_obj = objects_vec.at(i);

		bool colliding = true;

		while ( colliding )
		{
			colliding = box_in_box( obj->x() + x_add, obj->y() + y_add, obj->w(), obj->h(), other_obj->x(), other_obj->y(), other_obj->w(), other_obj->h() );

			if ( !colliding )
			{
				break;
			}
			else
			{
				x_add /= 2;
				y_add /= 2;
				i=0;

				if ( x_add == 0 && y_add == 0 )
				{
					return false;
				}
			}
		}
	}

	obj->x(obj->x() + + x_add);
	obj->y(obj->y() + y_add);

	return true;
}

bool colliding( object* obj, unsigned short dir)
{
	int temp_x = obj->x();
	int temp_y = obj->y();
	int temp_w = obj->w();
	int temp_h = obj->h();

	switch(dir)
	{
	case 0:
		if ( temp_y != 0 )
		{
			temp_y -= 1;
			temp_h += 1;
		}

		break;
	case 1:
		temp_w += 1;

		break;
	case 2:
		temp_h += 1;

		break;
	case 3:
		if ( temp_x != 0 )
		{
			temp_x -= 1;
			temp_w += 1;
		}

		break;
	}

	std::vector<object*> tmp = get_adjacents(obj);

	for ( unsigned i=0; i < tmp.size(); i++ )
	{
		const object* adj = tmp[i];

		if ( box_in_box( temp_x, temp_y, temp_w, temp_h, adj->x(), adj->y(), adj->w(), adj->h() ) )
		{
			return true;
		}
	}

	return false;
}

void handle_speeds( object* obj )
{
	vel_accel* va = dynamic_cast<vel_accel*>(obj);

	if ( !va )
	{
		return;
	}

	if ( !move_phys(obj, va->h_speed(), va->v_speed()) )
	{
		if ( !move_phys(obj, va->h_speed(),0) )
		{
			move_phys(obj, 0,va->v_speed());
		}
	}

	va->h_speed( va->h_speed() + va->h_accel() );
	va->v_speed( va->v_speed() + va->v_accel() );

	if ( colliding(obj,2) && va->v_speed() > 0 )
	{
		va->v_speed(0);
	}

	if ( colliding(obj,0) && va->v_speed() < 0 )
	{
		va->v_speed(0);
	}

	if ( colliding(obj,1) && va->h_speed() > 0 )
	{
		va->h_speed(0);
	}

	if ( colliding(obj,3) && va->h_speed() < 0 )
	{
		va->h_speed(0);
	}
}

std::vector<object*> get_adjacents( object* obj )
{
	std::vector<object*> ret;
	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( obj );

	unsigned temp_x = obj->x();
	unsigned temp_y = obj->y();
	unsigned temp_w = obj->w();
	unsigned temp_h = obj->h();

	if ( temp_x != 0 )
	{
		temp_x -= 1;
		temp_w += 2;
	}
	else
	{
		temp_w += 1;
	}

	if ( temp_y != 0 )
	{
		temp_y -= 1;
		temp_h += 2;
	}
	else
	{
		temp_h += 1;
	}

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		object* other_obj = objects_vec.at(i);

		if ( box_in_box( temp_x, temp_y, temp_w, temp_h, other_obj->x(), other_obj->y(), other_obj->w(), other_obj->h() ) )
		{
			ret.push_back(other_obj);
		}
	}

	return ret;
}
