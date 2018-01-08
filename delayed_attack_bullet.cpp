#include "delayed_attack_bullet.h"
#include "manager.h"
#include "attack_box.h"
#include "attackable.h"

delayed_attack_bullet::delayed_attack_bullet()
{
	animation.texture(manager::instance()->resources.textures("test"));
}

delayed_attack_bullet::~delayed_attack_bullet()
{
}

void delayed_attack_bullet::perform()
{
	dimens.x( att.owner()->dimens.x() + offset.x() );
	dimens.y( att.owner()->dimens.y() + offset.y() );
	speeds.h_speed(5);

	attack_box* ab = new attack_box();
	ab->set_attack(att);
	ab->lifespan(0);
	ab->speeds = speeds;
	ab->die_oob(true);
	ab->dimens = dimens;
	ab->animation = animation;

	manager::instance()->the_map.add_object(ab);
}
