#include "delayed_attack_bullet.h"
#include "manager.h"
#include "attack_box.h"
#include "attackable.h"
#include "creature.h"
#include "vel_accel.h"
#include <fstream>

delayed_attack_bullet::delayed_attack_bullet()
	:_speed(5)
{
	dimens.w(24);
	dimens.h(24);
	animation.texture(manager::instance()->resources.textures("laser_bullet"));
	animation.w(24);
	animation.h(3);
}

delayed_attack_bullet::~delayed_attack_bullet()
{
}

void delayed_attack_bullet::speed(float speed)
{
	_speed = speed;
}

float delayed_attack_bullet::speed() const
{
	return _speed;
}

void delayed_attack_bullet::perform()
{
	vel_accel speeds;
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
			speeds.v_speed(speed() + att.owner()->speeds.v_speed());
		}
		else
		{
			dimens.y( att.owner()->dimens.y() - offset.y() );
			speeds.v_speed(-speed() - att.owner()->speeds.v_speed());
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
			speeds.h_speed(-speed() - att.owner()->speeds.h_speed());
			dimens.x( att.owner()->dimens.x() - offset.x() );
			dimens.y( att.owner()->dimens.y() );
		}
		else
		{
			speeds.h_speed(speed() + att.owner()->speeds.h_speed());
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

void delayed_attack_bullet::load_data_from_file(std::string path)
{
	std::string full_path = manager::instance()->data_path() + "attack-info/" + path;

	std::string buf;
	int tmp_i;
	std::ifstream ifs(full_path);

	while ( ifs >> buf )
	{
		if ( buf == "animation" )
		{
			ifs >> buf;
			animation.texture(manager::instance()->resources.textures(buf));
		}
		else if ( buf == "sound" )
		{
			ifs >> buf;
			att.sound(buf);
		}
		else if ( buf == "width" )
		{
			ifs >> tmp_i;
			dimens.w(tmp_i);
		}
		else if ( buf == "height" )
		{
			ifs >> tmp_i;
			dimens.h(tmp_i);
		}
		else if ( buf == "damage" )
		{
			ifs >> tmp_i;
			att.damage(tmp_i);
		}
		else if ( buf == "knockback" )
		{
			ifs >> tmp_i;
			att.knockback(tmp_i);
		}
		else if ( buf == "delay" )
		{
			ifs >> tmp_i;
			action.delay(tmp_i);
		}
		else if ( buf == "speed" )
		{
			ifs >> tmp_i;
			speed(tmp_i);
		}
		else if ( buf == "cooldown" )
		{
			ifs >> tmp_i;
			action.cooldown(tmp_i);
		}
		else
		{
			std::string msg = "invalid attack-info for '" + full_path + "'";
			SDL_Log(msg.c_str());
			exit(1);
		}
	}
}
