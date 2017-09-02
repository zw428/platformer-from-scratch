#include "object.h"

#include <vector>

unsigned long object::_id_counter = 0;

object::object()
	:gravity_affected()
{
	set_collision_object(this);
	_id = _id_counter++;
}

bool object::operator==(const object& obj)
{
	return _id == obj._id;
}

unsigned long object::id() const
{
	return _id;
}
