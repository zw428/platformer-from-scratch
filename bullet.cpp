#include "bullet.h"
#include "collider.h"
#include "block.h"
#include "manager.h"

bullet::bullet()
	:_speed(5),
	 _reversed(false),
	 _theta(0)
{
	dimens.w(5);
	dimens.h(5);
	solid(false);
	lifespan(0);
	animation.texture(manager::instance()->resources.textures("test"));
}

void bullet::reverse()
{
	_reversed = !_reversed;
}

bool bullet::think()
{
	bool ret = attack_box::think();

	short x = _speed*std::cos( _theta * M_PI / 180 );
	short y = _speed*std::sin( _theta * M_PI / 180 );

	if ( _reversed )
	{
		x *= -1;
	}

	std::vector<box_object*> vec = move(this, x, y);

	for ( unsigned i=0; i < vec.size(); i++ )
	{
		if ( dynamic_cast<block*>(vec[i]) )
		{
			return true;
		}
	}

	animation.x(dimens.x());
	animation.y(dimens.y());
	animation.w(dimens.w());
	animation.h(dimens.h());
	animation.draw();

	return ret;
}
