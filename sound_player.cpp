#include "sound_player.h"
#include "manager.h"

sound_player::sound_player()
	:_sound(0)
{
}

void sound_player::play_sound()
{
	if ( _sound )
	{
		Mix_PlayChannel(-1, _sound, 0);
	}
}

void sound_player::sound( const char* sound_name )
{
	_sound = manager::instance()->sounds(sound_name);
}