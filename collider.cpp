#include "collider.h"
#include "manager.h"
#include "object.h"
#include "vel_accel.h"
#include "collide_functions.h"

void adjust_move_coords( box b, short& x_add, short& y_add )
{
	int map_size_x = manager::instance()->get_map()->x_size();
	int map_size_y = manager::instance()->get_map()->y_size();

	if ( int(b.x()) + x_add < 0 )
	{
		x_add = -b.x();
	}

	if ( int(b.x()) + x_add + b.w() > map_size_x )
	{
		x_add = map_size_x - b.x() - b.w();
	}

	if ( int(b.y()) + y_add < 0 )
	{
		y_add = -b.y();
	}

	if ( int(b.y()) + y_add + b.h() > map_size_y )
	{
		y_add = map_size_y - b.y() - b.h();
	}
}

std::vector<box_object*> move( box_object* bo, short x_add, short y_add )
{
	adjust_move_coords(bo->dimens, x_add, y_add);
	bo->dimens.x(bo->dimens.x() + x_add);
	bo->dimens.y(bo->dimens.y() + y_add);
	return manager::instance()->get_map()->box_objects_in_box( bo->dimens, bo );
}

bool move_phys( box_object* bo, short x_add, short y_add )
{
	if ( x_add == 0 && y_add == 0 )
	{
		return false;
	}

	adjust_move_coords(bo->dimens, x_add, y_add);

	std::vector<box_object*> bo_vec = manager::instance()->get_map()->box_objects_considered( bo );

	for ( unsigned i=0; i < bo_vec.size(); i++ )
	{
		const box_object* other_bo = bo_vec.at(i);

		if ( !other_bo->solid() )
		{
			continue;
		}

		bool colliding = true;

		while ( colliding )
		{
			colliding = box_in_box( bo->dimens.x() + x_add, bo->dimens.y() + y_add, bo->dimens.w(), bo->dimens.h(), other_bo->dimens.x(), other_bo->dimens.y(), other_bo->dimens.w(), other_bo->dimens.h() );

			if ( !colliding )
			{
				break;
			}
			else
			{
				bool colliding_horiz = box_in_box( bo->dimens.x() + x_add, bo->dimens.y(), bo->dimens.w(), bo->dimens.h(), other_bo->dimens.x(), other_bo->dimens.y(), other_bo->dimens.w(), other_bo->dimens.h() );
				bool colliding_vert = box_in_box( bo->dimens.x(), bo->dimens.y() + y_add, bo->dimens.w(), bo->dimens.h(), other_bo->dimens.x(), other_bo->dimens.y(), other_bo->dimens.w(), other_bo->dimens.h() );

				if ( colliding_horiz && !colliding_vert )
				{
					x_add /= 2;
				}
				else if ( colliding_vert && !colliding_horiz )
				{
					y_add /= 2;
				}
				else
				{
					x_add /= 2;
					y_add /= 2;
				}

				i=0;

				if ( x_add == 0 && y_add == 0 )
				{
					return false;
				}
			}
		}
	}

	bo->dimens.x(bo->dimens.x() + x_add);
	bo->dimens.y(bo->dimens.y() + y_add);

	return true;
}

bool colliding( box_object* bo, unsigned short dir)
{
	int temp_x = bo->dimens.x();
	int temp_y = bo->dimens.y();
	int temp_w = bo->dimens.w();
	int temp_h = bo->dimens.h();

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

	std::vector<box_object*> tmp = get_adjacents(bo);

	for ( unsigned i=0; i < tmp.size(); i++ )
	{
		const box_object* adj = tmp[i];

		if ( box_in_box( temp_x, temp_y, temp_w, temp_h, adj->dimens.x(), adj->dimens.y(), adj->dimens.w(), adj->dimens.h() ) )
		{
			return true;
		}
	}

	return false;
}

void handle_speeds( vel_accel& va, box_object* bo )
{
	if ( !bo )
	{
		return;
	}

	if ( !move_phys(bo, va.h_speed(), va.v_speed()) )
	{
		if ( !move_phys(bo, va.h_speed(),0) )
		{
			move_phys(bo, 0,va.v_speed());
		}
	}

	va.h_speed( va.h_speed() + va.h_accel() );
	va.v_speed( va.v_speed() + va.v_accel() );

	if ( colliding(bo,2) && va.v_speed() > 0 )
	{
		va.v_speed(0);
	}

	if ( colliding(bo,0) && va.v_speed() < 0 )
	{
		va.v_speed(0);
	}

	if ( colliding(bo,1) && va.h_speed() > 0 )
	{
		va.h_speed(0);
	}

	if ( colliding(bo,3) && va.h_speed() < 0 )
	{
		va.h_speed(0);
	}
}

std::vector<box_object*> get_adjacents( box_object* bo )
{
	std::vector<box_object*> ret;
	std::vector<box_object*> bo_vec = manager::instance()->get_map()->box_objects_considered( bo );

	unsigned temp_x = bo->dimens.x();
	unsigned temp_y = bo->dimens.y();
	unsigned temp_w = bo->dimens.w();
	unsigned temp_h = bo->dimens.h();

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

	for ( unsigned i=0; i < bo_vec.size(); i++ )
	{
		box_object* other_bo = bo_vec.at(i);

		if ( !other_bo->solid() )
		{
			continue;
		}

		if ( box_in_box( temp_x, temp_y, temp_w, temp_h, other_bo->dimens.x(), other_bo->dimens.y(), other_bo->dimens.w(), other_bo->dimens.h() ) )
		{
			ret.push_back(other_bo);
		}
	}

	return ret;
}
