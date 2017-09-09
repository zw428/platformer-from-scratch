#ifndef TRIGGER_H
#define TRIGGER_H

#include <vector>
#include "box.h"

class object;

class trigger : public box
{
public:
	trigger();
	virtual ~trigger();

	bool think();

	virtual bool action( object* ) = 0;

	const std::vector<object*> ignores();

	unsigned short lifespan() const;
	void lifespan( unsigned short lifespan );

	unsigned short interval() const;
	void interval( unsigned short interval );
private:
	unsigned short _lifespan;
	unsigned short _time_left;
	unsigned short _interval;

	struct object_interval {
		unsigned short counter;
		object* obj;
	};

	std::vector<object_interval> _ignores;
};

#endif
