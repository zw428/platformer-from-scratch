#include "block.h"
#include "manager.h"

block::block()
	  :_type(block_solid)
{
	_img.w(dimens.w());
	_img.h(dimens.h());
}

block::~block()
{
}

bool block::think_more()
{
	if ( _type != block_empty )
	{
		_img.x(dimens.x());
		_img.y(dimens.y());
		_img.w(dimens.w());
		_img.h(dimens.h());
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
		_img.texture(manager::instance()->resources.textures("test"));
		break;
	case block_empty:
		break;
	}
}
