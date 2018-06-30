#include "attack_manager.h"

attack_manager::attack_manager()
	:_current_attack(0),
	 _can_move(true)
{
}

void attack_manager::think(bool attacking, unsigned short direction, bool special, bool in_air, bool crouching)
{
	if ( _current_attack )
	{
		if ( !_current_attack->action.acting() )
		{
			_current_attack = 0;
			_can_move = true;
		}
		else
		{
			_current_attack->think(attacking);
		}
	}
	else if ( attacking )
	{
		if ( direction == 0 && special == true )
		{
			_current_attack = _up_special_attack.get();
		}
		else if ( direction == 1 && special == true )
		{
			_current_attack = _right_special_attack.get();
		}
		else if ( direction == 2 && special == true )
		{
			_current_attack = _down_special_attack.get();
		}
		else if ( direction == 3 && special == true )
		{
			_current_attack = _right_special_attack.get();
		}
		else if ( direction == 0 && in_air )
		{
			_current_attack = _up_air_attack.get();
		}
		else if ( direction == 1 && in_air )
		{
			_current_attack = _right_air_attack.get();
		}
		else if ( direction == 2 && in_air )
		{
			_current_attack = _down_air_attack.get();
		}
		else if ( direction == 3 && in_air )
		{
			_current_attack = _right_air_attack.get();
		}
		else if ( direction == 1 && crouching )
		{
			_current_attack = _crouching_attack.get();
		}
		else if ( direction == 3 && crouching )
		{
			_current_attack = _crouching_attack.get();
		}
		else if ( direction == 0 )
		{
			_current_attack = _up_attack.get();
		}
		else if ( direction == 1 )
		{
			_current_attack = _right_attack.get();
		}
		else if ( direction == 2 )
		{
			_current_attack = _down_attack.get();
		}
		else if ( direction == 3 )
		{
			_current_attack = _right_attack.get();
		}

		if ( _current_attack )
		{
			_current_attack->think(attacking);
			_can_move = false;
		}
	}
	else
	{
		_can_move = true;
	}

	if ( _up_attack.get() != 0 && _up_attack.get() != _current_attack )
	{
		_up_attack->think(false);
	}

	if ( _down_attack.get() != 0 && _down_attack.get() != _current_attack )
	{
		_down_attack->think(false);
	}

	if ( _right_attack.get() != 0 && _right_attack.get() != _current_attack )
	{
		_right_attack->think(false);
	}

	if ( _up_air_attack.get() != 0 && _up_air_attack.get() != _current_attack )
	{
		_up_air_attack->think(false);
	}

	if ( _down_air_attack.get() != 0 && _down_air_attack.get() != _current_attack )
	{
		_down_air_attack->think(false);
	}

	if ( _right_air_attack.get() != 0 && _right_air_attack.get() != _current_attack )
	{
		_right_air_attack->think(false);
	}

	if ( _up_special_attack.get() != 0 && _up_special_attack.get() != _current_attack )
	{
		_up_special_attack->think(false);
	}

	if ( _down_special_attack.get() != 0 && _down_special_attack.get() != _current_attack )
	{
		_down_special_attack->think(false);
	}

	if ( _right_special_attack.get() != 0 && _right_special_attack.get() != _current_attack )
	{
		_right_special_attack->think(false);
	}

	if ( _crouching_attack.get() != 0 && _crouching_attack.get() != _current_attack )
	{
		_crouching_attack->think(false);
	}

}

void attack_manager::set_up_attack(delayed_attack* da)
{
	_up_attack.reset(da);
}

void attack_manager::set_down_attack(delayed_attack* da)
{
	_down_attack.reset(da);
}

void attack_manager::set_right_attack(delayed_attack* da)
{
	_right_attack.reset(da);
}

void attack_manager::set_up_air_attack(delayed_attack* da)
{
	_up_air_attack.reset(da);
}

void attack_manager::set_down_air_attack(delayed_attack* da)
{
	_down_air_attack.reset(da);
}

void attack_manager::set_right_air_attack(delayed_attack* da)
{
	_right_air_attack.reset(da);
}

void attack_manager::set_up_special_attack(delayed_attack* da)
{
	_up_special_attack.reset(da);
}

void attack_manager::set_down_special_attack(delayed_attack* da)
{
	_down_special_attack.reset(da);
}

void attack_manager::set_right_special_attack(delayed_attack* da)
{
	_right_special_attack.reset(da);
}

bool attack_manager::can_move() const
{
	return _can_move;
}

void attack_manager::attack(unsigned short direction, bool special, bool in_air)
{
	if ( direction == 0 )
	{
	}
}
