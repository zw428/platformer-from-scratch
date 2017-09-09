#ifndef MAP_H
#define MAP_H

#include <vector>
#include <stack>
#include <memory>
#include <map>

#include <SDL2/SDL.h>

#include "chunk_prop.h"
#include "consts.h"
#include "trigger.h"

class object;
class block;

typedef std::vector<std::shared_ptr<object>> shared_obj_vec;

class map
{
public:
	map();
	map( unsigned x_size, unsigned y_size );

	void init( unsigned x_size, unsigned y_size ); //dimensions of map in pixels

	bool add_object( object* obj );
	bool add_trigger( trigger* tr );

	void think();

	unsigned short chunk_x_size();
	unsigned short chunk_y_size();
	unsigned x_size();
	unsigned y_size();

	void empty();

        std::vector<object*> objects_at( chunk_prop cp, object* ignore = 0 );
	std::vector<object*> objects_considered( object* obj );
private:
	void erase_object_from_grid( object* obj );
	void update_object_chunk( object* obj );

	std::vector<std::vector<std::vector<object*>>> _objects_grid;

	std::vector<std::shared_ptr<object>> _objects;

	std::vector<std::shared_ptr<trigger>> _triggers;

	unsigned short _chunk_x_size;
	unsigned short _chunk_y_size;

	unsigned _x_size;
	unsigned _y_size;

	chunk_prop obj_chunk_prop( object* obj );
	std::map<unsigned long, chunk_prop> _chunk_props;
};

#endif
