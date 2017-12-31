#include "catch.h"
#include "../directed_attack.h"
#include "../object.h"
#include "../attackable.h"
#include "../manager.h"

class directed_attack_tmp : public attackable
{
public:
	directed_attack_tmp() {};
	void receive_attack( const attack& att ) { attacked = true; };
	bool attacked = false;
};

TEST_CASE("directed_attack attacks in a given direction", "[directed_attack]")
{
	manager::instance()->get_map()->init(1000,1000);

	directed_attack_tmp* attacked = new directed_attack_tmp;

	manager::instance()->get_map()->add_object(attacked);

	attack tmp_attack;

	directed_attack d;

	box b;

	b.x(200);
	b.y(200);
	b.w(50);
	b.h(50);

	SECTION("up")
	{
		attacked->dimens.x(200);
		attacked->dimens.y(140);
		attacked->dimens.w(50);
		attacked->dimens.h(50);
		d.attack_up( tmp_attack, b, 20, 20 );
		manager::instance()->get_map()->think();

		CHECK( attacked->attacked == true );
	}

	SECTION("down")
	{
		attacked->dimens.x(200);
		attacked->dimens.y(260);
		attacked->dimens.w(50);
		attacked->dimens.h(50);
		attacked->attacked = false;
		d.attack_down( tmp_attack, b, 20, 20 );
		manager::instance()->get_map()->think();

		CHECK( attacked->attacked == true );
	}

	SECTION("left")
	{
		attacked->dimens.x(140);
		attacked->dimens.y(200);
		attacked->dimens.w(50);
		attacked->dimens.h(50);
		attacked->attacked = false;
		d.attack_left( tmp_attack, b, 20, 20 );
		manager::instance()->get_map()->think();

		CHECK( attacked->attacked == true );
	}

	SECTION("right")
	{
		attacked->dimens.x(260);
		attacked->dimens.y(200);
		attacked->dimens.w(50);
		attacked->dimens.h(50);
		attacked->attacked = false;
		d.attack_right( tmp_attack, b, 20, 20 );
		manager::instance()->get_map()->think();

		CHECK( attacked->attacked == true );
	}
}
