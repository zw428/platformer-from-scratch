#include "resource_manager.h"
#include "manager.h"
#include <sstream>

resource_manager::resource_manager()
{
}

bool resource_manager::add_texture(std::string path, std::string name)
{
	SDL_Texture* tex = NULL;

	std::string full_path = manager::instance()->data_path() + "images/" + path;

	SDL_Surface* surface = IMG_Load( full_path.c_str() );

	if ( !surface )
	{
		printf( "image load fail '%s'; sdl_image error: %s\n", path.c_str(), IMG_GetError() );
		return false;
	}

	tex = SDL_CreateTextureFromSurface( manager::instance()->renderer(), surface );

	if ( !tex )
	{
		printf( "couldn't create texture '%s'; sdl error: %s\n", path.c_str(), SDL_GetError() );
		return false;
	}

	SDL_FreeSurface( surface );

	texture_store ts;
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	ts.orig_w = w;
	ts.orig_h = w;
	ts.tex = tex;

	_textures[name] = ts;

	return true;
}

bool resource_manager::add_sound(std::string path, std::string name)
{
	std::string full_path = manager::instance()->data_path() + "sounds/" + path;

	Mix_Chunk* chunk = Mix_LoadWAV( full_path.c_str() );

	if ( !chunk )
	{
		printf( "sdl mix Error: %s\n", Mix_GetError() );
		return false;
	}

	_sounds[name] = chunk;

	return true;
}

bool resource_manager::add_font(std::string path, std::string name)
{
	std::string full_path = manager::instance()->data_path() + "fonts/" + path;

	TTF_Font* font = TTF_OpenFont( full_path.c_str(), 64 );

	if ( !font )
	{
		printf( "sdl font load error for font: %s\n", path.c_str() );
		return false;
	}

	_fonts[name] = font;

	return true;
}

texture_store resource_manager::textures(std::string texture_name)
{
	texture_store* ret = &_textures[texture_name];

	if ( ret )
	{
		return *ret;
	}
	else
	{
		texture_store tmp;
		tmp.orig_w = 0;
		tmp.orig_h = 0;
		tmp.tex = 0;

		return tmp;
	}
}

Mix_Chunk* resource_manager::sounds(std::string sound_name)
{
	Mix_Chunk* ret = _sounds[sound_name];

	if ( ret )
	{
		return ret;
	}
	else
	{
		return 0;
	}
}

Mix_Music* resource_manager::musics(std::string music_name)
{
	Mix_Music* ret = _musics[music_name];

	if ( ret )
	{
		return ret;
	}
	else
	{
		return 0;
	}
}

TTF_Font* resource_manager::fonts(std::string font_name)
{
	TTF_Font* ret = _fonts[font_name];

	if ( ret )
	{
		return ret;
	}
	else
	{
		return 0;
	}
}


void resource_manager::destroy_textures()
{
	for ( std::map<std::string, texture_store>::iterator i = _textures.begin(); i != _textures.end(); i++ )
	{
		SDL_DestroyTexture(i->second.tex);
	}

	_textures.clear();
}

void resource_manager::destroy_musics()
{
	for ( std::map<std::string, Mix_Music*>::iterator i = _musics.begin(); i != _musics.end(); i++ )
	{
		Mix_FreeMusic(i->second);
	}

	_musics.clear();
}

void resource_manager::destroy_sounds()
{
	for ( std::map<std::string, Mix_Chunk*>::iterator i = _sounds.begin(); i != _sounds.end(); i++ )
	{
		Mix_FreeChunk(i->second);
	}

	_sounds.clear();
}

void resource_manager::destroy_fonts()
{
	for ( std::map<std::string, TTF_Font*>::iterator i = _fonts.begin(); i != _fonts.end(); i++ )
	{
		TTF_CloseFont(i->second);
	}

	_fonts.clear();
}
