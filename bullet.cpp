#include "bullet.h"
#include "collider.h"
#include "block.h"

bullet::bullet()
	:_speed(5),
	 _reversed(false),
	 _theta(0)
{
	w(5);
	h(5);
	solid(false);
	lifespan(0);
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

	std::vector<object*> vec = move(this,x,y);

	draw();

	for ( unsigned i=0; i < vec.size(); i++ )
	{
		if ( dynamic_cast<block*>(vec[i]) )
		{
			return true;
		}
	}

	return ret;
}
