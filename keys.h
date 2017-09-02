#ifndef KEYS_H
#define KEYS_H

#include <SDL2/SDL.h>
#include <map>

class keys
{
public:
	void think( SDL_Event* ev );

	bool key_pressed( SDL_Keycode code );
	bool mouse_pressed( unsigned short button );

	unsigned mouse_x();
	unsigned mouse_y();

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
