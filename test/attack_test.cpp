#include "catch.h"

#include "../attack.h"
#include "../attackable.h"
	
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
	class performed_on : public attackable
	{
	public:
		bool received = false;

		void receive_attack( const attack& att )
		{
			received = true;
		}
	};

	attack att;
	att.damage(5);

	performed_on tmp;

	att.perform(dynamic_cast<attackable*>(&tmp));

	REQUIRE( tmp.received == true );
}
