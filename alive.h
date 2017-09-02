#ifndef ALIVE_H
#define ALIVE_H

#include "attack.h"

class alive
{
public:
	alive();

	void receive_attack( const attack& att );

	void health( unsigned short health );
	void armor( unsigned short armor );
	unsigned short health() const;
	unsigned short armor() const;
private:
	unsigned short _health;
	unsigned short _armor;
};

#endif
