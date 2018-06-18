#include "map.h"
#include <cmath>
#include <vector>
#include "manager.h"
#include "object.h"
#include "collide_functions.h"
#include "trigger.h"

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
	_objects_grid.clear();
	_root.empty();

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
	_root.add_child(obj);

	box_object* bo = dynamic_cast<box_object*>(obj);

	if ( bo )
	{
		update_box_object_chunk( bo );
	}

	return true;
}

void map::erase_box_object_from_grid( box_object* bo )
{
	chunk_prop cp = _chunk_props[ bo->id() ];

	std::vector<box_object*>& vec = _objects_grid[cp.x][cp.y];

	for ( unsigned i=0; i < vec.size(); i++ )
	{
		if ( vec[i] == bo )
		{
			_objects_grid[cp.x][cp.y].erase( _objects_grid[cp.x][cp.y].begin() + i);
			break;
		}
	}
}

void map::think()
{
	_root.think();
}

void map::update_box_object_chunk( box_object* bo )
{
	bool new_obj = ( _chunk_props.find( bo->id() ) == _chunk_props.end() );

	bool need_obj_update = false;

	box b = bo->dimens;

	chunk_prop cp = box_chunk_prop( b );
	chunk_prop old_cp = _chunk_props[ bo->id() ];

	need_obj_update = ( old_cp != cp );

	if ( need_obj_update )
	{
		erase_box_object_from_grid(bo);
	}

	if ( new_obj || need_obj_update )
	{
		std::vector<box_object*>& vec = _objects_grid[cp.x][cp.y];
		vec.push_back(bo);
		_chunk_props[ bo->id() ] = cp;
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
	init(_x_size, _y_size);
}

std::vector<box_object*> map::box_objects_in_box( box b, box_object* ignore )
{
	std::vector<box_object*> ret;

	chunk_prop cp;

	for ( unsigned i = b.left() / CHUNK_SIZE; i <= b.right() / CHUNK_SIZE; i++ )
	{
		cp.x = i;

		for ( unsigned j = b.top() / CHUNK_SIZE; j <= b.bottom() / CHUNK_SIZE; j++ )
		{
			cp.y = j;
			std::vector<box_object*> tmp = box_objects_in_chunk( cp );

			for ( unsigned k=0; k < tmp.size(); k++ )
			{
				if ( box_in_box( tmp[k]->dimens, b ) && tmp[k] != ignore )
				{
					ret.push_back(tmp[k]);
				}
			}
		}
	}

	return ret;
}

std::vector<box_object*> map::box_objects_in_chunk( chunk_prop cp, box_object* ignore )
{
	std::vector<box_object*> ret;

	if ( cp.x >= chunk_x_size() || cp.y >= chunk_y_size() )
	{
		return ret;
	}

	std::vector<box_object*>& vec = _objects_grid[cp.x][cp.y];

	for ( unsigned i=0; i < vec.size(); i++ )
	{
		if ( vec[i] != ignore )
		{
			ret.push_back(vec[i]);
		}
	}

	return ret;
}

std::vector<box_object*> map::box_objects_considered( box_object* bo )
{
	chunk_prop cp = box_chunk_prop(bo->dimens);

	if ( cp.x >= chunk_x_size() )
	{
		cp.x = chunk_x_size() - 1;
	}

	if ( cp.y >= chunk_x_size() )
	{
		cp.y = chunk_y_size() - 1;
	}

	std::vector<box_object*> ret;

	chunk_prop temp_cp = cp;

	for ( int x=-1; x <= 1; x++ )
	{
		for ( int y=-1; y <= 1; y++ )
		{
			temp_cp.x += x;
			temp_cp.y += y;

			if ( temp_cp.x >= 0 && temp_cp.x < chunk_x_size() && temp_cp.y >= 0 && temp_cp.y < chunk_y_size() )
			{
				std::vector<box_object*> tmp = box_objects_in_chunk( temp_cp, bo );
				ret.insert( ret.end(), tmp.begin(), tmp.end() );
			}

			temp_cp = cp;
		}
	}

	return ret;
}

chunk_prop map::box_chunk_prop( box b )
{
	chunk_prop ret;

	ret.x = b.x()/CHUNK_SIZE;
	ret.y = b.y()/CHUNK_SIZE;

	return ret;
}
