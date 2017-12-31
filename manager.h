#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include "map.h"
#include "resource_manager.h"
#include "level_loader.h"
#include "camera.h"

class object;

class manager
{
public:
	bool init( bool no_window = false );
	bool main_loop();
        static manager* instance();
        static void destroy();

	std::string data_path() const;
	void data_path( std::string path );

	resource_manager resources;
	level_loader loader;
	camera cam;

	SDL_Renderer* renderer();
	map the_map;
private:
	manager();

	const char* _game_title;
	std::string _data_path_prefix;

	SDL_Window* _win;
	SDL_Renderer* _ren;
	SDL_Event _ev;

	const unsigned short _window_w;
	const unsigned short _window_h;
	unsigned char _draw_color[4];

	static manager* _instance;
};

#endif
