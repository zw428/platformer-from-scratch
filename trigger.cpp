#include "trigger.h"
#include "manager.h"
#include "box_object.h"
#include "collide_functions.h"

trigger::trigger()
	:_lifespan(0),
	 _time_left(1),
	 _interval(30),
	 _enabled(true)
{
	solid(false);
}

trigger::~trigger()
{
}

bool trigger::think()
{
	box_object::think();

	if ( !enabled() )
	{
		return false;
	}

	if ( _lifespan )
	{
		if ( _time_left > 0 )
		{
			_time_left -= 1;
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

	std::vector<box_object*> box_objects_vec = manager::instance()->get_map()->box_objects_in_box(dimens, this);

	for ( unsigned i=0; i < box_objects_vec.size(); i++ )
	{
		bool will_continue = false;

		box_object* bo = box_objects_vec.at(i);

		for ( unsigned j=0; j < _ignores.size(); j++ )
		{
			if ( _ignores[j].bo == bo )
			{
				will_continue = true;
				break;
			}
		}

		if ( will_continue )
		{
			continue;
		}

		if ( box_in_box( dimens, bo->dimens ) )
		{
			if ( action(box_objects_vec[i]) )
			{
				return true;
			}

			if ( interval() )
			{
				object_interval tmp;

				unsigned short tmp_interval = 0;

				if ( interval() > 0 )
				{
					tmp_interval = interval() - 1;
				}

				tmp.counter = tmp_interval;
				tmp.bo = box_objects_vec[i];

				_ignores.push_back(tmp);
			}
		}
	}

	if ( _time_left == 0 )
	{
		return true;
	}

	return false;
}

unsigned short trigger::lifespan() const
{
	return _lifespan;
}

void trigger::lifespan( unsigned short lifespan )
{
	_lifespan = lifespan;
}

unsigned short trigger::interval() const
{
	return _interval;
}

void trigger::interval( unsigned short interval )
{
	_interval = interval;
}

bool trigger::enabled() const
{
	return _enabled;
}

void trigger::enabled( bool enabled )
{
	_enabled = enabled;
}
