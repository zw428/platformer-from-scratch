#include "death_box.h"
#include "alive.h"
#include "object.h"

death_box::death_box()
{
	lifespan(0);
	interval(0);
}

death_box::~death_box()
{
}

bool death_box::action( object* obj )
{
	alive* al = dynamic_cast<alive*>(obj);

	if ( al )
	{
		al->health(0);
	}

	return false;
}
