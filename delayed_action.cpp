#include "delayed_action.h"

delayed_action::delayed_action()
	:_delay(20),
	 _cooldown(20),
	 _cooldown_counter(0),
	 _acting(false),
	 _ready(false)
{
	 _delay_counter = _delay;
}

void delayed_action::think( bool starting )
{
	_ready = false;

	if ( starting && !_acting && _cooldown_counter == 0 )
	{
		_acting = true;
		_delay_counter = delay();
		_cooldown_counter = cooldown();
	}

	if ( _cooldown_counter > 0 )
	{
		_cooldown_counter--;
	}

	if ( !_acting )
	{
		return;
	}

	if ( _delay_counter > 0 )
	{
		_delay_counter--;
	}

	if ( _delay_counter == 0 )
	{
		_acting = false;
		_ready = true;
	}
}

void delayed_action::delay( unsigned short delay )
{
	_delay = ( delay ) ? delay : 2;
}

void delayed_action::cooldown( unsigned short cooldown )
{
	_cooldown = ( cooldown ) ? cooldown : 2;
}

unsigned short delayed_action::delay() const
{
	return _delay;
}

unsigned short delayed_action::cooldown() const
{
	return _cooldown;
}

bool delayed_action::acting() const
{
	return _acting;
}

bool delayed_action::cooling_down() const
{
	return _cooldown_counter != 0;
}

bool delayed_action::ready() const
{
	return _ready;
}
