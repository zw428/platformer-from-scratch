#pragma once

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "texture_store.h"

class resource_manager
{
public:
	resource_manager();

	texture_store textures( std::string texture_name );
	Mix_Chunk* sounds(std::string sound_name);
	Mix_Music* musics(std::string music_name);
	TTF_Font* fonts(std::string font_name);

	bool add_texture( std::string path, std::string name );
	bool add_sound(std::string path, std::string name);
	bool add_font(std::string path, std::string name);

	void destroy_textures();
	void destroy_musics();
	void destroy_sounds();
	void destroy_fonts();
private:
	std::map<std::string, texture_store> _textures;
	std::map<std::string, Mix_Chunk*> _sounds;
	std::map<std::string, Mix_Music*> _musics;
	std::map<std::string, TTF_Font*> _fonts;
};

#endif
