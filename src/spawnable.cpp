#include "spawnable.h"

spawnable::spawnable()
	:_spawn_delay(0),
	 _spawning(false)
{
	_spawn_timer = _spawn_delay;
}

spawnable::~spawnable()
{
}

void spawnable::spawn()
{
	_spawning = true;
}

void spawnable::handle_spawning()
{
	if ( spawning() && _spawn_timer > 0 )
	{
		_spawn_timer--;
	}
	else
	{
		on_spawn();
		_spawn_timer = spawn_delay();
		_spawning = false;
	}
}

void spawnable::spawn_delay( unsigned delay )
{
	_spawn_delay = delay;
}

unsigned spawnable::spawn_delay() const
{
	return _spawn_delay;
}

bool spawnable::spawning() const
{
	return _spawning;
}
