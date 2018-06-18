#include "knockback.h"
#include "attackable.h"

void knockback( attackable* atbl, double hit_angle, const attack& att )
{
	vel_accel& va = atbl->speeds;

	double mult=1;

	if ( atbl->type() == attackable_knockback_multiplier )
	{
		mult += atbl->health() / 20;
	}

	va.h_speed( float(att.knockback()) * cos(hit_angle*M_PI/180) * mult );
	va.v_speed( float(att.knockback()) * sin(hit_angle*M_PI/180) * mult );
}
