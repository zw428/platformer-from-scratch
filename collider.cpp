#include "collider.h"
#include "manager.h"
#include "object.h"
#include "collide_functions.h"

collider::collider()
	:movable(), box()
{
}

collider::collider( object* obj )
	:movable()
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
		return move_phys(1-x(),y_add);
	}

	if ( int(x()) + x_add + w() > map_size_x )
	{
		return move_phys(map_size_x - x() - w() - 1,y_add);
	}

	if ( int(y()) + y_add < 0 )
	{
		return move_phys(x_add,1-y());
	}

	if ( int(y()) + y_add + h() > map_size_y )
	{
		return move_phys(x_add,map_size_y - y() - h() - 1);
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
	switch(dir)
	{
	case 0:
		for ( unsigned i=0; i < _adjacents.size(); i++ )
		{
			if ( _adjacents[i]->y() + _adjacents[i]->h() == y() )
			{
				return true;
			}
		}
		break;
	case 1:
		for ( unsigned i=0; i < _adjacents.size(); i++ )
		{
			if ( _adjacents[i]->x() + _adjacents[i]->w() == x() )
			{
				return true;
			}
		}
		break;
	case 2:
		for ( unsigned i=0; i < _adjacents.size(); i++ )
		{
			if ( _adjacents[i]->y() == y() + h() )
			{
				return true;
			}
		}
		break;
	case 3:
		for ( unsigned i=0; i < _adjacents.size(); i++ )
		{
			if ( _adjacents[i]->x() == x() + w() )
			{
				return true;
			}
		}
		break;
	}

	return false;
}

void collider::handle_speeds()
{
	move_phys(h_speed(),v_speed());

	h_speed( h_speed() + h_accel() );
	v_speed( v_speed() + v_accel() );

	if ( colliding(2) )
	{
		v_speed(0);
	}

	if ( colliding(0) )
	{
		v_speed(1);
	}

	if ( colliding(1) || colliding(3) )
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
