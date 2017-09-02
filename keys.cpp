#include "keys.h"

keys* keys::_instance = 0;

bool keys::key_pressed( SDL_Keycode code )
{
	if ( _keys_pressed.find( code ) == _keys_pressed.end() )
	{
		return false;
	}

	return _keys_pressed[code];

}

bool keys::mouse_pressed( unsigned short button )
{
	if ( button == 0 )
	{
		return _mouse_pressed[0];
	}

	return _mouse_pressed[1];
}

unsigned keys::mouse_x()
{
	return _mouse_x;
}

unsigned keys::mouse_y()
{
	return _mouse_y;
}

void keys::think( SDL_Event* ev )
{
	switch( ev->type )
	{
	case SDL_MOUSEMOTION:
		_mouse_x = ev->motion.x;
		_mouse_y = ev->motion.y;
		break;

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:

		switch(ev->button.button)
		{
			case SDL_BUTTON_LEFT:
				_mouse_pressed[0] = ( ev->type == SDL_MOUSEBUTTONDOWN );
				break;

			case SDL_BUTTON_RIGHT:
				_mouse_pressed[1] = ( ev->type == SDL_MOUSEBUTTONDOWN );
				break;
		}
		break;

	case SDL_KEYDOWN:

		_keys_pressed[ev->key.keysym.sym] = true;
		break;

	case SDL_KEYUP:

		_keys_pressed[ev->key.keysym.sym] = false;
		break;
	}
}

keys::keys()
{
	_mouse_pressed[0] = _mouse_pressed[1] = false;
}

keys* keys::instance()
{
	if ( !_instance )
	{
		_instance = new keys;
	}

	return _instance;
}
