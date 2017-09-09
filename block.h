#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"
#include "image.h"

enum block_type
{
	empty, solid
};

class block : public object
{
public:
	block();
	~block();
	bool think();

	bool is_solid() const;

	void type( block_type type );
private:
	block_type _type;

	image _img;
};

#endif
