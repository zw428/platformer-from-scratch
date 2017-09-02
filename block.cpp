#include "block.h"
#include "manager.h"

block::block()
	 :object()
{
	_img.w(w());
	_img.h(h());

	weightless(true);
}

bool block::think()
{
	if ( _type != empty )
	{
		_img.x(x());
		_img.y(y());
		_img.w(w());
		_img.h(h());
		_img.draw();
	}

	return false;
}

void block::handle_keys( SDL_Event* ev )
{
}

bool block::is_solid()
{
	return ( _type != block_type::empty );
}

void block::type( block_type type )
{
	_type = type;

	switch(_type)
	{
	case solid:
		_img.texture(manager::instance()->textures("test"));
		break;
	case empty:
		break;
	}
}
