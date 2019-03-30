#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include "box_object.h"
#include "image.h"

enum block_type
{
	block_empty, block_solid
};

class block : public box_object
{
public:
	block();
	~block();
	bool think_more();

	bool is_solid() const;

	void type( block_type type );
private:
	block_type _type;

	image _img;
};

#endif
