#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>

#include <SDL2/SDL.h>

#include "chunk_prop.h"
#include "consts.h"
#include "box.h"
#include "box_object.h"

class map
{
public:
	map();
	map( unsigned x_size, unsigned y_size );

	void init( unsigned x_size, unsigned y_size ); //dimensions of map in pixels

	bool add_object( object* obj );

	void think();

	unsigned short chunk_x_size() const;
	unsigned short chunk_y_size() const;
	unsigned x_size() const;
	unsigned y_size() const;

	void empty();

	void erase_box_object_from_grid( box_object* bo );
	void update_box_object_chunk( box_object* bo );

        std::vector<box_object*> box_objects_in_box( box b, box_object* ignore = 0 );
        std::vector<box_object*> box_objects_in_chunk( chunk_prop cp, box_object* ignore = 0 );
	std::vector<box_object*> box_objects_considered( box_object* b );
private:
	object _root;

	std::vector<std::vector<std::vector<box_object*>>> _objects_grid;

	unsigned _x_size;
	unsigned _y_size;

	chunk_prop box_chunk_prop( box b );
	std::map<unsigned long, chunk_prop> _chunk_props;
};

#endif
