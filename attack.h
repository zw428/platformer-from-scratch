#ifndef ATTACK_H
#define ATTACK_H

#include <SDL2/SDL_mixer.h>

class alive;

class attack
{
public:
	attack();

	void damage( unsigned short damage );
	unsigned short damage() const;

	void knockback( unsigned short knockback );
	unsigned short knockback() const;

	alive* owner();
	void owner( alive* own );

	void perform( alive* al );

	void play_sound();
	void sound( const char* sound_name );
private:
	void reset_delay();

	unsigned short _damage;
	unsigned short _knockback;

	Mix_Chunk* _sound;
	alive* _owner;
};

#endif
