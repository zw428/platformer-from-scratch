#include "death_box.h"
#include "object.h"
#include "death.h"

death_box::death_box()
	:trigger()
{
	lifespan(0);
	interval(0);
}

death_box::~death_box()
{
}

bool death_box::action( object* obj )
{
	death* d = dynamic_cast<death*>(obj);

	if ( d )
	{
		d->on_death();
	}

	return false;
}
