#ifndef ALIVE_H
#define ALIVE_H

#include "attack.h"

class alive
{
public:
	alive();
	virtual ~alive();

	virtual void receive_attack( const attack& att );

	void health( unsigned short health );
	unsigned short health() const;
private:
	unsigned short _health;
};

#endif
