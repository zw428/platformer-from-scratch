#ifndef TRIGGER_H
#define TRIGGER_H

#include <vector>
#include "box_object.h"

class trigger : public box_object
{
public:
	trigger();
	virtual ~trigger();

	bool think();

	virtual bool action( box_object* ) = 0;

	const std::vector<object*> ignores();

	unsigned short lifespan() const;
	void lifespan( unsigned short lifespan );

	unsigned short interval() const;
	void interval( unsigned short interval );

	bool enabled() const;
	void enabled( bool enabled );
private:
	unsigned short _lifespan;
	unsigned short _time_left;
	unsigned short _interval;

	bool _enabled;

	struct object_interval {
		unsigned short counter;
		box_object* bo;
	};

	std::vector<object_interval> _ignores;
};

#endif
