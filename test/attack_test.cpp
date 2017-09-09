#include "catch.hpp"

#include "../attack.h"
#include "../attackable.h"
	
TEST_CASE( "constructor initializes values", "[attack]" )
{
	attack att;

	REQUIRE( att.damage() == 0 );
	REQUIRE( att.knockback() == 0 );
}

TEST_CASE( "attack setters and getters work", "[attack]" )
{
	SECTION( "non-const" )
	{
		attack att;
		att.damage(5);
		att.knockback(5);
		att.owner(0);
		REQUIRE( att.damage() == 5 );
		REQUIRE( att.knockback() == 5 );
		REQUIRE( att.owner() == 0 );
	}

	SECTION( "const" )
	{
		attack att;
		att.damage(5);
		att.knockback(5);
		att.owner(0);
		const attack& const_att = att;
		REQUIRE( const_att.damage() == 5 );
		REQUIRE( const_att.knockback() == 5 );
		REQUIRE( const_att.owner() == 0 );
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
