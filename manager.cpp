#include "manager.h"

#include <fstream>
#include <sstream>
#include <string>
#include "object.h"
#include "player.h"
#include "npc.h"
#include "block.h"
#include "keys.h"
#include "text.h"

manager* manager::_instance = 0;

manager::manager()
	:_game_title("unknown"),
	 _data_path_prefix("./data/"),
	 _window_w(1024),
	 _window_h(768)
{
	manager::_instance = this;

	_map.init(1024,768);
}

manager* manager::instance()
{
	if ( !_instance )
	{
		_instance = new manager;
	}

	return _instance;
}

bool manager::init()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "sdl init video error: %s\n", SDL_GetError() );
		return false;
	}

	if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "no linear texture filturing\n" );
	}

	_win = SDL_CreateWindow( _game_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_w, _window_h, SDL_WINDOW_SHOWN );

	if ( !_win )
	{
		printf( "sdl window error: %s\n", SDL_GetError() );
		return false;
	}

	_ren = SDL_CreateRenderer( _win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	if ( !_ren  )
	{
		printf( "sdl renderer error: %s\n", SDL_GetError() );
		return false;
	}

	SDL_SetRenderDrawColor( _ren, 0, 0, 0, 0);

	int img_flags = IMG_INIT_PNG;

	if ( !( IMG_Init( img_flags ) & img_flags ) )
	{
		printf( "sdl image Error: %s\n", IMG_GetError() );
		return false;
	}

	if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
	{
		printf( "sdl mix Error: %s\n", Mix_GetError() );
		return false;
	}

	int flags = MIX_INIT_OGG;

	int initted = Mix_Init( flags );

	if ( (initted & flags) != flags )
	{
		printf( "sdl mix Error: %s\n", Mix_GetError() );
		return false;
	}

	if ( TTF_Init() == -1 )
	{
		printf( "sdl ttf Error" );
		return false;
	}

	image::set_renderer(_ren);

	keys::instance();

	main_loop();

	return true;
}

texture_store manager::textures(const char* texture_name)
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

Mix_Chunk* manager::sounds(const char* sound_name)
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

Mix_Music* manager::musics(const char* music_name)
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

TTF_Font* manager::fonts(const char* font_name)
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

SDL_Renderer* manager::renderer()
{
	return _ren;
}

map* manager::get_map()
{
	return &_map;
}

bool manager::main_loop()
{
	bool quit = false;

	load_level("level0");

	while( !quit )
	{
		while( SDL_PollEvent( &_ev ) != 0 )
		{
			if ( _ev.type == SDL_QUIT )
			{
				quit = true;
			}

			if ( _ev.type == SDL_MOUSEMOTION || _ev.type == SDL_KEYDOWN || _ev.type == SDL_KEYUP || _ev.type == SDL_MOUSEBUTTONDOWN || _ev.type == SDL_MOUSEBUTTONUP )
			{
				keys::instance()->think(&_ev);
			}
		}

		SDL_RenderClear( _ren );

		//draw grid

		SDL_SetRenderDrawColor( _ren, 32, 32, 32, 32 );

		for ( unsigned i=0; i < _window_w / CHUNK_SIZE; i++ )
		{
			SDL_RenderDrawLine( _ren, i*CHUNK_SIZE, 0, i*CHUNK_SIZE, _window_h );
		}

		for ( unsigned j=0; j < _window_h / CHUNK_SIZE; j++ )
		{
			SDL_RenderDrawLine( _ren, 0, j*CHUNK_SIZE, _window_w, j*CHUNK_SIZE );
		}

		SDL_SetRenderDrawColor( _ren, 0, 0, 0, 0);

		//objects think

		_map.think();

		SDL_RenderPresent( _ren );
	}

	for ( std::map<std::string, texture_store>::iterator i = _textures.begin(); i != _textures.end(); i++ )
	{
		SDL_DestroyTexture(i->second.tex);
	}

	for ( std::map<std::string, Mix_Chunk*>::iterator i = _sounds.begin(); i != _sounds.end(); i++ )
	{
		Mix_FreeChunk(i->second);
	}

	for ( std::map<std::string, Mix_Music*>::iterator i = _musics.begin(); i != _musics.end(); i++ )
	{
		Mix_FreeMusic(i->second);
	}

	for ( std::map<std::string, TTF_Font*>::iterator i = _fonts.begin(); i != _fonts.end(); i++ )
	{
		TTF_CloseFont(i->second);
	}

	SDL_DestroyRenderer( _ren );
	SDL_DestroyWindow( _win );
	IMG_Quit();
	Mix_Quit();

	return true;
}

bool manager::add_texture(const char* path, const char* name)
{
	SDL_Texture* tex = NULL;

	char full_path[256];
	strcpy(full_path,_data_path_prefix);
	strcat(full_path,path);

	SDL_Surface* surface = IMG_Load( full_path );

	if ( !surface )
	{
		printf( "image load fail '%s'; sdl_image error: %s\n", path, IMG_GetError() );
		return false;
	}

	tex = SDL_CreateTextureFromSurface( _ren, surface );

	if ( !tex )
	{
		printf( "couldn't create texture '%s'; sdl error: %s\n", path, SDL_GetError() );
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

bool manager::add_sound(const char* path, const char* name)
{
	char full_path[256];
	strcpy(full_path,_data_path_prefix);
	strcat(full_path,path);

	Mix_Chunk* chunk = Mix_LoadWAV( full_path );

	if ( !chunk )
	{
		printf( "sdl mix Error: %s\n", Mix_GetError() );
		return false;
	}

	_sounds[name] = chunk;

	return true;
}

bool manager::add_font(const char* path, const char* name)
{
	char full_path[256];
	strcpy(full_path,_data_path_prefix);
	strcat(full_path,path);

	TTF_Font* font = TTF_OpenFont( full_path, 64 );

	if ( !font )
	{
		printf( "sdl font load error for font: %s\n", path );
		return false;
	}

	_fonts[name] = font;

	return true;
}

bool manager::load_level(const char* path)
{
	char full_path[256];
	strcpy(full_path,_data_path_prefix);
	strcat(full_path,path);

	std::string buf;
	std::ifstream ifs(full_path);

	while ( ifs >> buf )
	{
		if ( buf == "texture" )
		{
			std::getline(ifs,buf);
			process_texture_str(buf.c_str());
		}

		if ( buf == "sound" )
		{
			std::getline(ifs,buf);
			process_sound_str(buf.c_str());
		}

		if ( buf == "character" )
		{
			std::getline(ifs,buf);
			process_character_str(buf.c_str());
		}

		if ( buf == "block" )
		{
			std::getline(ifs,buf);
			process_block_str(buf.c_str());
		}

		if ( buf == "font" )
		{
			std::getline(ifs,buf);
			process_font_str(buf.c_str());
		}
	}

	ifs.close();

	return true;
}

bool manager::process_font_str(const char* str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	add_font( path.c_str(), name.c_str() );

	return true;
}

bool manager::process_texture_str(const char* str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	add_texture(path.c_str(),name.c_str());

	return true;
}

bool manager::process_character_str(const char* str)
{
	std::stringstream ss(str);
	std::string type, image_name, x, y;

	ss >> type;
	ss >> x;
	ss >> y;

	unsigned short x_num = std::stoi(x);
	unsigned short y_num = std::stoi(y);

	if ( type == "player" )
	{
		player* temp = new player;
		temp->x(x_num);
		temp->y(y_num);
		_map.add_object(dynamic_cast<object*>(temp));
	}
	else if ( type == "npc" )
	{
		npc* temp = new npc;
		temp->dest(x_num,y_num);
		temp->x(x_num);
		temp->y(y_num);
		_map.add_object(dynamic_cast<object*>(temp));
	}


	return true;
}

bool manager::process_sound_str(const char* str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	add_sound(path.c_str(),name.c_str());

	return true;
}

bool manager::process_block_str(const char* str)
{
	std::stringstream ss(str);
	std::string image_name, x, y, w, h;

	ss >> image_name;
	ss >> x;
	ss >> y;
	ss >> w;
	ss >> h;

	block* temp = new block;

	temp->x(std::stoi(x));
	temp->y(std::stoi(y));
	temp->w(std::stoi(w));
	temp->h(std::stoi(h));

	temp->type( solid );

	_map.add_object(temp);

	return true;
}
