#pragma once

#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <SDL2/SDL_mixer.h>
#include <string>

class sound_player
{
public:
	sound_player();
	void play_sound();
	void sound( std::string sound_name );
private:
	Mix_Chunk* _sound;
};

#endif
