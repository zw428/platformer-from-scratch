#include "catch.h"

#include "../attack.h"
#include "../attackable.h"
	
class attack_test_tmp : public attackable
{
public:
	bool received = false;

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
