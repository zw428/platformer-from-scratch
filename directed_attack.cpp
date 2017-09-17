#include "directed_attack.h"
#include "attack_box.h"
#include "manager.h"

directed_attack::directed_attack()
{
}

void directed_attack::attack_up( const attack& att, box* source, unsigned w, unsigned h )
{
	attack_in_dir( att, source, 0, w, h );
}

void directed_attack::attack_down( const attack& att, box* source, unsigned w, unsigned h )
{
	attack_in_dir( att, source, 2, w, h );
}

void directed_attack::attack_left( const attack& att, box* source, unsigned w, unsigned h )
{
	attack_in_dir( att, source, 3, w, h );
}

void directed_attack::attack_right( const attack& att, box* source, unsigned w, unsigned h )
{
	attack_in_dir( att, source, 1, w, h );
}

void directed_attack::attack_in_dir( const attack& att, box* source, unsigned short dir, unsigned w, unsigned h )
{
	attack_box* b = new attack_box();
	b->set_attack(att);

	b->w(w);
	b->h(h);

	switch( dir )
	{
	case 0:
		b->x( source->x_center() - w / 2 );
		b->y( source->top() - h );
		break;
	case 1:
		b->x( source->right() );
		b->y( source->y_center() - h / 2 );
		break;
	case 2:
		b->x( source->x_center() - w / 2 );
		b->y( source->bottom() );
		break;
	case 3:
		b->x( source->left() - w );
		b->y( source->y_center() - h / 2 );
		break;
	}

	manager::instance()->get_map()->add_trigger( b );
}
