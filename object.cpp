#include "object.h"
#include "box_object.h"
#include "manager.h"

#include <vector>

unsigned long object::_id_counter = 0;

object::object()
{
	_id = _id_counter++;
}

object::~object()
{
}

bool object::think()
{
	if ( think_more() )
	{
		return true;
	}

	for ( unsigned i=0; i < _children.size(); i++ )
	{
		box_object* bo = dynamic_cast<box_object*>(_children[i]);

		if ( _children[i]->think() )
		{
			remove_child_by_index(i);

			if ( bo )
			{
				manager::instance()->the_map.erase_box_object_from_grid( bo );
			}
		}
		else if ( bo )
		{
			manager::instance()->the_map.update_box_object_chunk( bo );
		}

	}

	return false;
}

bool object::think_more()
{
	return false;
}


void object::add_child(object* obj)
{
	_children.push_back(obj);
}

bool object::remove_child(object* obj)
{
	for ( unsigned i=0; i < _children.size(); i++ )
	{
		if ( _children[i] == obj )
		{
			remove_child_by_index(i);
			return true;
		}
	}

	for ( unsigned i=0; i < _children.size(); i++ )
	{
		if ( _children[i]->remove_child(obj) )
		{
			return true;
		}
	}

	return false;
}

object* object::child_at_index(unsigned i)
{
	if ( i > _children.size() - 1 )
	{
		SDL_Log("invalid object child index");
		exit(1);
	}

	return _children[i];
}

unsigned object::children_size() const
{
	return _children.size();
}

bool object::operator==(const object& obj)
{
	return _id == obj._id;
}

bool object::operator!=(const object& obj)
{
	return _id != obj._id;
}

unsigned long object::id() const
{
	return _id;
}

void object::empty()
{
	for ( unsigned i=0; i < _children.size(); i++ )
	{
		remove_child_by_index(i);
	}
}

void object::remove_child_by_index(unsigned& i)
{
	delete _children[i];
	_children.erase( _children.begin() + i-- );
}
