#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include "map.h"
#include "resource_manager.h"
#include "level_loader.h"
#include "camera.h"

class object;

class manager : public resource_manager, public level_loader, public camera
{
public:
	bool init();
        static manager* instance();

	std::string data_path();
	void data_path( std::string path );

	SDL_Renderer* renderer();
	map* get_map();
private:
	manager();

	bool main_loop();

	const char* _game_title;
	std::string _data_path_prefix;

	SDL_Window* _win;
	SDL_Renderer* _ren;
	SDL_Event _ev;

	const unsigned short _window_w;
	const unsigned short _window_h;
	unsigned char _draw_color[4];

	map _map;

	static manager* _instance;
};

#endif
