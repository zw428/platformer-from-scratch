#include "catch.h"

#include "../attack.h"
#include "../attackable.h"
#include "../object.h"

class attack_test_tmp : public attackable
{
public:
	bool received = false;

	bool think() { return false; }

	void receive_attack( const attack& att )
	{
		received = true;
	}
};

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

	att.perform(&tmp, 0);

	REQUIRE( tmp.received == true );
}

TEST_CASE( "attack will not perform on owner", "[attack]" )
{
	attack att;
	att.damage(5);

	attack_test_tmp tmp;

	att.owner(&tmp);

	att.perform(&tmp, 0);

	REQUIRE( tmp.received == false );
}
