#include "object.h"

#include <vector>

unsigned long object::_id_counter = 0;

object::object()
	:box(),
	 _solid(true)
{
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

void object::solid( bool solid )
{
	_solid = solid;
}

bool object::solid() const
{
	return _solid;
}
