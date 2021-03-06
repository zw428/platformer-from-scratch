#include "ledge_grabber.h"
#include "box.h"
#include "block.h"
#include "manager.h"
#include "box_object.h"
#include <vector>

short h_dist_between_boxes( box source, box b )
{
	if ( source.x() < b.x() )
	{
		return ( b.left() - source.right() );
	}
	else
	{
		return ( b.right() - source.left() );
	}
}

ledge_grabber::ledge_grabber()
	:_dist_to_ledge(0),
	 _h_dist_to_ledge(0),
	 _found_ledge(false),
	 _letting_go(false),
	 _hanging(false)
{
}

unsigned short ledge_grabber::dist_to_ledge() const
{
	return _dist_to_ledge;
}

short ledge_grabber::h_dist_to_ledge() const
{
	return _h_dist_to_ledge;
}

bool ledge_grabber::found_ledge() const
{
	return _found_ledge;
}

bool ledge_grabber::hanging() const
{
	return _hanging;
}

void ledge_grabber::find_ledge( vel_accel& va, box b, bool on_ground )
{
	if ( va.v_speed() <= 0 || on_ground )
	{
		return;
	}

	if ( _letting_go )
	{
		_letting_go = false;
		return;
	}

	box left = b;
	left.w( 10 );
	left.x( b.x() - 10 );
	left.h( b.h()*2 );

	box right = b;
	right.x( b.right() + 1 );
	right.w( 10 );
	right.h( b.h()*2 );

	std::vector<box_object*> tmp = manager::instance()->the_map.box_objects_in_box( left );
	std::vector<box_object*> right_objects = manager::instance()->the_map.box_objects_in_box( right );
	tmp.insert( tmp.end(), right_objects.begin(), right_objects.end() );

	unsigned short smallest_dist = -1;

	_found_ledge = false;

	for ( unsigned i=0; i < tmp.size(); i++ )
	{
		if ( dynamic_cast<block*>(tmp[i]) )
		{
			unsigned short dist = tmp[i]->dimens.top() - b.top();

			if ( dist < smallest_dist )
			{
				smallest_dist = dist;
				_h_dist_to_ledge = h_dist_between_boxes( b, tmp[i]->dimens );
			}

			_found_ledge = true;
		}
	}

	_dist_to_ledge = smallest_dist;

	if ( found_ledge() && dist_to_ledge() < 10 )
	{
		attach_to_ledge( va );
	}
}

void ledge_grabber::let_go()
{
	_found_ledge = false;
	_dist_to_ledge = -1;
	_letting_go = true;
	_hanging = false;
}

void ledge_grabber::attach_to_ledge( vel_accel& va )
{
	va.v_accel(0);
	va.h_accel(0);

	if ( va.v_speed() > dist_to_ledge() )
	{
		va.v_speed( dist_to_ledge() );
	}

	if ( va.v_speed() == 0 )
	{
		if ( h_dist_to_ledge() > 0 )
		{
			va.h_speed(4);
		}
		else if ( h_dist_to_ledge() < 0 )
		{
			va.h_speed(-4);
		}
	}

	_hanging = true;
}
