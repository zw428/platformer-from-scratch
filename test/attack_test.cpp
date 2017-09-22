#include "catch.h"

#include "../attack.h"
#include "../attackable.h"
#include "../object.h"
	
class attack_test_tmp : public attackable, public object
{
public:
	bool received = false;

	bool think() { return false; }

	void receive_attack( const attack& att )
	{
		received = true;
	}
};

TEST_CASE( "constructor initializes values", "[attack]" )
{
	attack att;

	CHECK( att.damage() == 0 );
	CHECK( att.knockback() == 0 );
	CHECK( att.owner() == 0 );
}

TEST_CASE( "attack setters and getters work", "[attack]" )
{
	SECTION( "non-const" )
	{
		attack att;
		att.damage(5);
		att.knockback(5);
		att.owner(0);
		CHECK( att.damage() == 5 );
		CHECK( att.knockback() == 5 );
		CHECK( att.owner() == 0 );
	}
}

TEST_CASE( "attack=(attack) works", "[attack]" )
{
	SECTION( "non-const" )
	{
		attack att;
		att.damage(37);
		att.knockback(38);
		att.owner(0);

		attack att2 = att;
		CHECK( att2.damage() == 37 );
		CHECK( att2.knockback() == 38 );
		CHECK( att2.owner() == 0 );
	}
}

TEST_CASE( "attack can perform on something", "[attack]" )
{
	attack att;
	att.damage(5);

	attack_test_tmp tmp;

	att.perform(&tmp);

	REQUIRE( tmp.received == true );
}

TEST_CASE( "attack will not perform on owner", "[attack]" )
{
	attack att;
	att.damage(5);

	attack_test_tmp tmp;

	att.owner(&tmp);

	att.perform(&tmp);

	REQUIRE( tmp.received == false );
}
