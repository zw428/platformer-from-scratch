#include "delayed_attack_box.h"
#include <fstream>

#include "manager.h"
#include "attack_box.h"
#include "attackable.h"
#include "creature.h"

delayed_attack_box::delayed_attack_box()
	:add_as_child(false),
	 _lifespan(30)
{
	animation.texture(manager::instance()->resources.textures("test"));
}

delayed_attack_box::~delayed_attack_box()
{
}

void delayed_attack_box::perform()
{
	dimens.y( att.owner()->dimens.y() + offset.y() );
	
	creature* c = dynamic_cast<creature*>(att.owner());

	if ( left_was_pressed() )
	{
		dimens.x( att.owner()->dimens.x() - offset.x() );
	}
	else
	{
		dimens.x( att.owner()->dimens.x() + offset.x() );
	}

	attack_box* ab = new attack_box();
	ab->set_attack(att);
	ab->lifespan(lifespan());
	animation.x(dimens.x());
	animation.y(dimens.y());
	animation.w(dimens.w());
	animation.h(dimens.h());

	ab->animation = animation;

	ab->dimens = dimens;

	if ( add_as_child && c )
	{
		c->add_child(ab);
	}
	else
	{
		manager::instance()->the_map.add_object(ab);
	}
}

unsigned short delayed_attack_box::lifespan() const
{
	return _lifespan;
}

void delayed_attack_box::lifespan(unsigned short t)
{
	_lifespan = t;
}

void delayed_attack_box::load_data_from_file(std::string path)
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
		else if ( buf == "hitAngle" )
		{
			ifs >> tmp_i;
			att.hit_angle(tmp_i);
		}
		else if ( buf == "xOffset" )
		{
			ifs >> tmp_i;
			offset.x(tmp_i);
		}
		else if ( buf == "yOffset" )
		{
			ifs >> tmp_i;
			offset.y(tmp_i);
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
		else if ( buf == "cooldown" )
		{
			ifs >> tmp_i;
			action.cooldown(tmp_i);
		}
		else if ( buf == "addAsChild" )
		{
			ifs >> tmp_i;
			add_as_child = tmp_i;
		}
		else if ( buf == "lifespan" )
		{
			ifs >> tmp_i;
			lifespan(tmp_i);
		}
		else
		{
			std::string msg = "invalid attack-info for '" + full_path + "'";
			SDL_Log(msg.c_str());
			exit(1);
		}
	}
}
