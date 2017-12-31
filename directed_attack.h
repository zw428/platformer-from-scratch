#ifndef DIRECTED_ATTACK_H
#define DIRECTED_ATTACK_H

#include "attack.h"
#include "box.h"

class directed_attack
{
public:
	directed_attack();
	void attack_up( const attack& att, box source, unsigned w, unsigned h );
	void attack_down( const attack& att, box source, unsigned w, unsigned h );
	void attack_left( const attack& att, box source, unsigned w, unsigned h );
	void attack_right( const attack& att, box source, unsigned w, unsigned h );
private:
	void attack_in_dir( const attack& att, box source, unsigned short dir, unsigned w, unsigned h );
};

#endif
