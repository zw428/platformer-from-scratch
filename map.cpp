#include "map.h"
#include <cmath>
#include <vector>
#include "manager.h"
#include "object.h"
#include "collide_functions.h"

map::map()
	:_x_size(0),
	 _y_size(0)
{
}

map::map( unsigned x_size, unsigned y_size )
{
	init( x_size, y_size );
}

void map::init( unsigned x_size, unsigned y_size )
{
	empty();

	x_size -= x_size % CHUNK_SIZE;
	y_size -= y_size % CHUNK_SIZE;

	_x_size = x_size;
	_y_size = y_size;

	_objects_grid.resize(chunk_x_size());

	for ( unsigned i=0; i < chunk_x_size(); i++ )
	{
		_objects_grid[i].resize(chunk_y_size());
	}
}

bool map::add_object(object* obj)
{
	std::shared_ptr<object> shared_obj;

	shared_obj.reset(obj);

	_objects.push_back(shared_obj);

	update_object_chunk( obj );

	return true;
}

bool map::add_trigger(trigger* tr)
{
	std::shared_ptr<trigger> shared_trigger;

	shared_trigger.reset(tr);

	_triggers.push_back(shared_trigger);

	return true;
}

void map::erase_object_from_grid( object* obj )
{
	chunk_prop cp = _chunk_props[ obj->id() ];

	std::vector<object*>& vec = _objects_grid[cp.x][cp.y];

	for ( unsigned i=0; i < vec.size(); i++ )
	{
		if ( vec[i] == obj )
		{
			vec.erase( vec.begin() + i );
			break;
		}
	}
}

void map::think()
{
	for ( unsigned i=0; i < _objects.size(); i++ )
	{
		std::shared_ptr<object> shared_obj = _objects[i];
		object* obj = shared_obj.get();

		if ( obj->think() )
		{
			_objects.erase( _objects.begin() + i-- );
			erase_object_from_grid( obj );
		}
		else
		{
			update_object_chunk( obj );
		}

	}

	for ( unsigned i=0; i < _triggers.size(); i++ )
	{
		std::shared_ptr<trigger> shared_trigger = _triggers[i];
		trigger* tr = shared_trigger.get();

		if ( tr->think() )
		{
			_triggers.erase( _triggers.begin() + i-- );
		}
	}
}

void map::update_object_chunk( object* obj )
{
	bool new_obj = ( _chunk_props.find( obj->id() ) == _chunk_props.end() );

	bool need_obj_update = false;

	chunk_prop cp = obj_chunk_prop( obj );
	chunk_prop old_cp = _chunk_props[ obj->id() ];

	need_obj_update = ( old_cp != cp );

	if ( need_obj_update )
	{
		erase_object_from_grid(obj);
	}

	if ( new_obj || need_obj_update )
	{
		std::vector<object*>& vec = _objects_grid[cp.x][cp.y];
		vec.push_back(obj);
		_chunk_props[ obj->id() ] = cp;
	}
}

unsigned short map::chunk_x_size() const
{
	return x_size() / CHUNK_SIZE;
}

unsigned short map::chunk_y_size() const
{
	return y_size() / CHUNK_SIZE;
}

unsigned map::x_size() const
{
	return _x_size;
}

unsigned map::y_size() const
{
	return _y_size;
}

void map::empty()
{
	_objects.clear();
	_objects_grid.clear();
	_triggers.clear();
	_x_size = 0;
	_y_size = 0;
}

std::vector<object*> map::objects_in_box( box* b, object* ignore )
{
	std::vector<object*> ret;

	if ( !b )
	{
		return ret;
	}

	chunk_prop cp;

	for ( unsigned i = b->left() / CHUNK_SIZE; i <= b->right() / CHUNK_SIZE; i++ )
	{
		cp.x = i;

		for ( unsigned j = b->top() / CHUNK_SIZE; j <= b->bottom() / CHUNK_SIZE; j++ )
		{
			cp.y = j;
			std::vector<object*> tmp = objects_in_chunk( cp );

			for ( unsigned k=0; k < tmp.size(); k++ )
			{
				if ( box_in_box( tmp[k], b ) && tmp[k] != ignore )
				{
					ret.push_back(tmp[k]);
				}
			}
		}
	}

	return ret;
}

std::vector<object*> map::objects_in_chunk( chunk_prop cp, object* ignore )
{
	std::vector<object*> ret;

	if ( cp.x >= chunk_x_size() || cp.y >= chunk_y_size() )
	{
		return ret;
	}

	std::vector<object*>& vec = _objects_grid[cp.x][cp.y];

	for ( unsigned i=0; i < vec.size(); i++ )
	{
		if ( vec[i] != ignore )
		{
			ret.push_back(vec[i]);
		}
	}

	return ret;
}

std::vector<object*> map::objects_considered( object* obj )
{
	chunk_prop cp = obj_chunk_prop(obj);

	if ( cp.x >= chunk_x_size() )
	{
		cp.x = chunk_x_size() - 1;
	}

	if ( cp.y >= chunk_x_size() )
	{
		cp.y = chunk_y_size() - 1;
	}

	std::vector<object*> ret;

	chunk_prop temp_cp = cp;

	for ( int x=-1; x <= 1; x++ )
	{
		for ( int y=-1; y <= 1; y++ )
		{
			temp_cp.x += x;
			temp_cp.y += y;

			if ( temp_cp.x >= 0 && temp_cp.x < chunk_x_size() && temp_cp.y >= 0 && temp_cp.y < chunk_y_size() )
			{
				std::vector<object*> tmp = objects_in_chunk( temp_cp, obj );
				ret.insert( ret.end(), tmp.begin(), tmp.end() );
			}

			temp_cp = cp;
		}
	}

	return ret;
}

chunk_prop map::obj_chunk_prop( object* obj )
{
	chunk_prop ret;

	ret.x = obj->x()/CHUNK_SIZE;
	ret.y = obj->y()/CHUNK_SIZE;

	return ret;
}
