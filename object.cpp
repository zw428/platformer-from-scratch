#include "object.h"

#include <vector>

unsigned long object::_id_counter = 0;

object::object()
	:jumper()
{
	set_collision_object(this);
	_id = _id_counter++;
}

object::~object()
{
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
