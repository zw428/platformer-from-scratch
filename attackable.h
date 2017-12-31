#ifndef ATTACKABLE_H
#define ATTACKABLE_H

#include "box_object.h"

class attack;

class attackable : public box_object
{
public:
	attackable();
	virtual void receive_attack( const attack& att ) = 0;
};

#endif
