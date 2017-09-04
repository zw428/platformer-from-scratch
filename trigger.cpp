#include "trigger.h"
#include "manager.h"
#include "object.h"
#include "collide_functions.h"

trigger::trigger( unsigned short lifespan )
	:_time_left(1),
	 _interval(30)
{
	_lifespan = lifespan;
}

trigger::~trigger()
{
}

bool trigger::think()
{
	static unsigned short time_left = ( _lifespan ? _lifespan : 1 );

	if ( _lifespan )
	{
		if ( time_left > 0 )
		{
			time_left -= 1;
		}
	}

	for ( unsigned i=0; i < _ignores.size(); i++ )
	{
		if ( _ignores[i].counter > 0 )
		{
			_ignores[i].counter--;
		}
		else
		{
			_ignores.erase(_ignores.begin() + i--);
		}
	}

	chunk_prop cp;
	cp.x = x() / CHUNK_SIZE;
	cp.y = y() / CHUNK_SIZE;

	std::vector<object*> objects_vec;

	for ( unsigned i = cp.x; i < (x() + w()) / CHUNK_SIZE; i++ )
	{
		cp.x = i;
		for ( unsigned j = cp.y; j < (y() + h()) / CHUNK_SIZE; j++ )
		{
			cp.y = j;
			std::vector<object*> tmp = manager::instance()->get_map()->objects_at( cp );
			objects_vec.insert( objects_vec.end(), tmp.begin(), tmp.end() );
		}
	}

	for ( unsigned i=0; i < objects_vec.size(); i++ )
	{
		bool will_continue = false;

		object* obj = objects_vec.at(i);

		for ( unsigned j=0; j < _ignores.size(); j++ )
		{
			if ( _ignores[j].obj == obj )
			{
				will_continue = true;
				break;
			}
		}

		if ( will_continue )
		{
			continue;
		}

		if ( box_in_box( x(), y(), w(), h(), obj->x(), obj->y(), obj->w(), obj->h() ) )
		{
			if ( action(objects_vec[i]) )
			{
				return true;
			}

			if ( interval() )
			{
				object_interval tmp;
				tmp.counter = interval();
				tmp.obj = objects_vec[i];

				_ignores.push_back(tmp);
			}
		}
	}

	if ( time_left == 0 )
	{
		return true;
	}

	return false;
}

unsigned short trigger::lifespan()
{
	return _lifespan;
}

void trigger::lifespan( unsigned short lifespan )
{
	_lifespan = lifespan;
}

unsigned short trigger::interval()
{
	return _interval;
}

void trigger::interval( unsigned short interval )
{
	_interval = interval;
}
