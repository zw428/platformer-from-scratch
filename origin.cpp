#include "origin.h"

origin::origin()
	:_o(origin_top)
{
}

void origin::set_dir( origins o )
{
	_o = o;
}

origins origin::dir() const
{
	return _o;
}

void origin::apply( box& child, box parent )
{
	if ( child.w() != parent.w() )
	{
		switch( _o )
		{
		case origin_top:
		case origin_bottom:
		case origin_center:
			child.x( parent.x_center() - child.w() / 2 );
			break;
		case origin_tr:
		case origin_right:
		case origin_br:
			child.x( parent.right() - child.w() );
			break;
		case origin_bl:
		case origin_left:
		case origin_tl:
			child.x( parent.left() );
			break;
		}
	}

	if ( child.h() != parent.h() )
	{
		switch( _o )
		{
		case origin_top:
		case origin_tr:
		case origin_tl:
			child.y( parent.top() );
			break;
		case origin_right:
		case origin_left:
		case origin_center:
			child.y( parent.y_center() - child.h() / 2 );
			break;
		case origin_br:
		case origin_bottom:
		case origin_bl:
			child.y( parent.bottom() - child.h() );
			break;
		}
	}
}
