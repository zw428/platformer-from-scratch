#include "ledge_grabber.h"
#include "box.h"
#include "block.h"
#include "manager.h"
#include <vector>

short h_dist_between_boxes( box* source, box* b )
{
	if ( !source || !b )
	{
		throw("tried to get distance between a null box");
	}

	if ( source->x() < b->x() )
	{
		return ( b->left() - source->right() );
	}
	else
	{
		return ( b->right() - source->left() );
	}
}

ledge_grabber::ledge_grabber()
	:_dist_to_ledge(0),
	 _h_dist_to_ledge(0),
	 _found_ledge(false),
	 _letting_go(false)
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

void ledge_grabber::find_ledge( box* b )
{
	if ( !b )
	{
		return;
	}

	if ( _letting_go )
	{
		_letting_go = false;
		return;
	}

	box left = *b;
	left.w( 10 );
	left.x( b->x() - 10 );
	left.h( b->h()*2 );

	box right = *b;
	right.x( b->right() + 1 );
	right.w( 10 );
	right.h( b->h()*2 );

	std::vector<object*> tmp = manager::instance()->get_map()->objects_in_box( &left );
	std::vector<object*> right_objects = manager::instance()->get_map()->objects_in_box( &right );
	tmp.insert( tmp.end(), right_objects.begin(), right_objects.end() );

	unsigned short smallest_dist = -1;

	_found_ledge = false;

	for ( unsigned i=0; i < tmp.size(); i++ )
	{
		if ( dynamic_cast<block*>(tmp[i]) )
		{
			unsigned short dist = tmp[i]->top() - b->top();

			if ( dist < smallest_dist )
			{
				smallest_dist = dist;
				_h_dist_to_ledge = h_dist_between_boxes( b, tmp[i] );
			}

			_found_ledge = true;
		}
	}

	_dist_to_ledge = smallest_dist;
}

void ledge_grabber::let_go()
{
	_found_ledge = false;
	_dist_to_ledge = -1;
	_letting_go = true;
}
