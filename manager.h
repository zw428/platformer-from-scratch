#ifndef MANAGER_H
#define MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include "map.h"

class object;

struct texture_store {
	SDL_Texture* tex;
	unsigned short orig_w;
	unsigned short orig_h;
};

class manager
{
public:
	bool init();
        static manager* instance();

	texture_store textures(const char* texture_name);
	Mix_Chunk* sounds(const char* sound_name);
	Mix_Music* musics(const char* music_name);
	TTF_Font* fonts(const char* font_name);

	SDL_Renderer* renderer();

	map* get_map();
private:
	manager();

	bool main_loop();

	bool add_texture(const char* path, const char* name);
	bool add_sound(const char* path, const char* name);
	bool add_font(const char* path, const char* name);

	bool load_level(const char* path);
	bool process_font_str(const char* str);
	bool process_texture_str(const char* str);
	bool process_character_str(const char* str);
	bool process_sound_str(const char* str);
	bool process_block_str(const char* str);

	const char* _game_title;

	const char* _data_path_prefix;

	SDL_Window* _win;
	SDL_Renderer* _ren;
	SDL_Event _ev;

	std::map<std::string, texture_store> _textures;
	std::map<std::string, Mix_Chunk*> _sounds;
	std::map<std::string, Mix_Music*> _musics;
	std::map<std::string, TTF_Font*> _fonts;

	const unsigned short _window_w;
	const unsigned short _window_h;
	unsigned char _draw_color[4];

	map _map;

	static manager* _instance;
};

#endif
