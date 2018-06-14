#include "delayed_attack_bullet.h"
#include "manager.h"
#include "attack_box.h"
#include "attackable.h"
#include "creature.h"
#include "vel_accel.h"

delayed_attack_bullet::delayed_attack_bullet()
{
	animation.texture(manager::instance()->resources.textures("test"));
}

delayed_attack_bullet::~delayed_attack_bullet()
{
}

void delayed_attack_bullet::perform()
{
	const unsigned short speed = 5;

	vel_accel speeds;
	box dimens;
	coords offset;

	offset.x(att.owner()->dimens.w());
	offset.y(att.owner()->dimens.h());

	dimens.x( att.owner()->dimens.x() );

	if ( down_was_pressed() || up_was_pressed() )
	{
		dimens.x( 1.5*att.owner()->dimens.x() - dimens.x() / 2);

		if ( down_was_pressed() )
		{
			dimens.y( att.owner()->dimens.y() + offset.y() );
			speeds.v_speed(speed);
		}
		else
		{
			dimens.y( att.owner()->dimens.y() - offset.y() );
			speeds.v_speed(-speed);
		}
	}
	else
	{
		bool facing_left = false;

		creature* c = dynamic_cast<creature*>(att.owner());

		if ( c )
		{
			facing_left = c->facing_left();
		}

		if ( facing_left )
		{
			speeds.h_speed(-speed);
			dimens.x( att.owner()->dimens.x() - offset.x() );
			dimens.y( att.owner()->dimens.y() );
		}
		else
		{
			speeds.h_speed(speed);
			dimens.x( att.owner()->dimens.x() + offset.x() );
			dimens.y( att.owner()->dimens.y() );
		}
	}

	attack_box* ab = new attack_box();
	ab->set_attack(att);
	ab->lifespan(0);
	ab->speeds = speeds;
	ab->die_oob(true);
	ab->die_on_collide(true);
	ab->dimens = dimens;
	ab->animation = animation;

	manager::instance()->the_map.add_object(ab);
}
