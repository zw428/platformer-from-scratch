#include "collider.h"
#include "manager.h"
#include "object.h"
#include "collide_functions.h"

collider::collider()
	:mover(), box()
{
}

collider::collider( object* obj )
	:mover(), box()
{
	set_collision_object(obj);
}

bool collider::move_phys( short x_add, short y_add )
{
	if ( x_add == 0 && y_add == 0 )
	{
		return false;
	}

	int map_size_x = manager::instance()->get_map()->x_size();
	int map_size_y = manager::instance()->get_map()->y_size();

	if ( int(x()) + x_add < 0 )
	{
		x_add = -x();
	}

	if ( int(x()) + x_add + w() > map_size_x )
	{
		x_add = map_size_x - x() - w();
	}

	if ( int(y()) + y_add < 0 )
	{
		y_add = -y();
	}

	if ( int(y()) + y_add + h() > map_size_y )
	{
		y_add = map_size_y - y() - h();
	}

	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( dynamic_cast<object*>( collision_object() ) );

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		const object* obj = objects_vec.at(i);

		if ( obj != collision_object() )
		{
			bool colliding = true;

			while ( colliding )
			{
				colliding = box_in_box( x() + x_add, y() + y_add, w(), h(), obj->x(), obj->y(), obj->w(), obj->h() );

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
	}

	x(x() + x_add);
	y(y() + y_add);

	get_adjacents( true );

	return true;
}

bool collider::colliding(unsigned short dir)
{
	int temp_x = x();
	int temp_y = y();
	int temp_w = w();
	int temp_h = h();

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

	for ( unsigned i=0; i < _adjacents.size(); i++ )
	{
		const object* adj = _adjacents[i];

		if ( box_in_box( temp_x, temp_y, temp_w, temp_h, adj->x(), adj->y(), adj->w(), adj->h() ) )
		{
			return true;
		}
	}
	return false;
}

void collider::handle_speeds()
{
	if ( !move_phys(h_speed(),v_speed()) )
	{
		if ( !move_phys(h_speed(),0) )
		{
			move_phys(0,v_speed());
		}
	}

	h_speed( h_speed() + h_accel() );
	v_speed( v_speed() + v_accel() );

	if ( colliding(2) && v_speed() > 0 )
	{
		v_speed(0);
	}

	if ( colliding(0) && v_speed() < 0 )
	{
		v_speed(0);
	}

	if ( colliding(1) && h_speed() > 0 )
	{
		h_speed(0);
	}

	if ( colliding(3) && h_speed() < 0 )
	{
		h_speed(0);
	}
}

void collider::set_collision_object( object* obj )
{
	_collision_obj = obj;
}

object* collider::collision_object()
{
	return _collision_obj;
}

void collider::get_adjacents( bool chain )
{
	_adjacents.clear();

	std::vector<object*> objects_vec = manager::instance()->get_map()->objects_considered( collision_object() );

	unsigned temp_x = x();
	unsigned temp_y = y();
	unsigned temp_w = w();
	unsigned temp_h = h();

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
		object* obj = objects_vec.at(i);

		if ( obj != collision_object() )
		{
			if ( box_in_box( temp_x, temp_y, temp_w, temp_h, obj->x(), obj->y(), obj->w(), obj->h() ) )
			{
				_adjacents.push_back(obj);

				if ( chain )
				{
					obj->get_adjacents( false );
				}
			}
        	}
	}
}
