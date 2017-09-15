#include "catch.hpp"
#include "../object.h"

class object_tmp : public object
{
public:
	bool think() { return false; };
};

TEST_CASE( "no two objects are alike", "[object]" )
{
	object_tmp obj;
	object_tmp obj2;

	CHECK( obj != obj2 );
}
