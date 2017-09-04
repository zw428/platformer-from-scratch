#include "disabled.h"

disabled::disabled()
	:_timer(0)
{
}

void disabled::handle_disabled()
{
	if ( is_disabled() )
	{
		_timer--;
	}
}

bool disabled::is_disabled()
{
	return _timer;
}

void disabled::disable( unsigned time )
{
	_timer = time;
}
