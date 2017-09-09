#ifndef KEYS_H
#define KEYS_H

#include <SDL2/SDL.h>
#include <map>

class keys
{
public:
	void think( SDL_Event* ev );

	static void reset();

	bool key_pressed( SDL_Keycode code );
	bool mouse_pressed( unsigned short button ) const;

	unsigned mouse_x() const;
	unsigned mouse_y() const;

	static keys* instance();
private:
	std::map<SDL_Keycode, bool> _keys_pressed;

	unsigned _mouse_x;
	unsigned _mouse_y;

	bool _mouse_pressed[2];

	keys();
	static keys* _instance;
};

#endif
