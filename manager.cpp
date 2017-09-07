#include "manager.h"

#include "keys.h"

manager* manager::_instance = 0;

manager::manager()
	:_game_title("unknown"),
	 _window_w(1024),
	 _window_h(768)
{
	data_path("./data/");
}

manager* manager::instance()
{
	if ( !_instance )
	{
		_instance = new manager;
	}

	return _instance;
}
std::string manager::data_path()
{
	return _data_path_prefix;
}

void manager::data_path( std::string path )
{
	_data_path_prefix = path;
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

	keys::instance();

	return true;
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

		//objects think

		_map.think();

		SDL_RenderPresent( _ren );
	}

	destroy_textures();
	destroy_musics();
	destroy_sounds();
	destroy_fonts();

	SDL_DestroyRenderer( _ren );
	SDL_DestroyWindow( _win );
	IMG_Quit();
	Mix_Quit();

	return true;
}
