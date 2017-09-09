#ifndef ALIVE_H
#define ALIVE_H

#include "attack.h"
#include "attackable.h"

class alive : public attackable
{
public:
	alive();
	~alive();
	void receive_attack( const attack& att );

	void health( unsigned short health );
	unsigned short health() const;
private:
	unsigned short _health;
};

#endif
