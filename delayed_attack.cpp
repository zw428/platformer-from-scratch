#include "delayed_attack.h"

delayed_attack::delayed_attack()
{
}

delayed_attack::~delayed_attack()
{
}

void delayed_attack::think( bool start_attack )
{
	action.think( start_attack );
	animation.draw();

	if ( action.ready() )
	{
		animation.show();
		perform();
	}
	else
	{
		animation.hide();
	}
}
