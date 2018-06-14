#include "delayed_attack.h"
#include "creature.h"

delayed_attack::delayed_attack()
	:_up_was_pressed(false),
	 _down_was_pressed(false),
	 _left_was_pressed(false),
	 _right_was_pressed(false),
	 _can_change_attack_dir(true)
{
}

delayed_attack::~delayed_attack()
{
}

void delayed_attack::think( bool start_attack )
{
	action.think( start_attack );

	creature* c = dynamic_cast<creature*>(att.owner());

	if ( c && _can_change_attack_dir && start_attack )
	{
		_up_was_pressed = c->up_pressed;
		_down_was_pressed = c->down_pressed;
		_left_was_pressed = c->left_pressed;
		_right_was_pressed = c->right_pressed;
		_can_change_attack_dir = false;
	}

	if ( action.ready() )
	{
		perform();
		_can_change_attack_dir = true;
	}
}

bool delayed_attack::up_was_pressed() const
{
	return _up_was_pressed;
}

bool delayed_attack::down_was_pressed() const
{
	return _down_was_pressed;
}

bool delayed_attack::left_was_pressed() const
{
	return _left_was_pressed;
}

bool delayed_attack::right_was_pressed() const
{
	return _right_was_pressed;
}
