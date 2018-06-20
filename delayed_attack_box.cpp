#include "delayed_attack_box.h"
#include "manager.h"
#include "attack_box.h"
#include "attackable.h"
#include "creature.h"

delayed_attack_box::delayed_attack_box()
	:add_as_child(false)
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
