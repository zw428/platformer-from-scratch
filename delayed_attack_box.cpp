#include "delayed_attack_box.h"
#include "manager.h"
#include "attack_box.h"
#include "attackable.h"

delayed_attack_box::delayed_attack_box()
{
	animation.texture(manager::instance()->resources.textures("test"));
}

delayed_attack_box::~delayed_attack_box()
{
}

void delayed_attack_box::perform()
{
	dimens.x( att.owner()->dimens.x() + offset.x() );
	dimens.y( att.owner()->dimens.y() + offset.y() );

	attack_box* ab = new attack_box();
	ab->set_attack(att);
	animation.x(dimens.x());
	animation.y(dimens.y());
	animation.w(dimens.w());
	animation.h(dimens.h());
	ab->animation = animation;

	ab->dimens = dimens;

	manager::instance()->the_map.add_object(ab);
}
