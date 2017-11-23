#include "block.h"
#include "manager.h"

block::block()
	 :object(),
	  _type(block_solid)
{
	_img.w(w());
	_img.h(h());
}

block::~block()
{
}

bool block::think()
{
	if ( _type != block_empty )
	{
		_img.x(x());
		_img.y(y());
		_img.w(w());
		_img.h(h());
		_img.draw();
	}

	return false;
}

bool block::is_solid() const
{
	return ( _type != block_type::block_empty );
}

void block::type( block_type type )
{
	_type = type;

	switch(_type)
	{
	case block_solid:
		_img.texture(manager::instance()->textures("test"));
		break;
	case block_empty:
		break;
	}
}
