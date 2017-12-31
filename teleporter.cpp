#include "teleporter.h"
#include "manager.h"
#include "box_object.h"
#include "collide_functions.h"

bool teleport( box_object* bo, int x, int y )
{
	std::vector<box_object*> bo_vec = manager::instance()->get_map()->box_objects_considered( bo );

	for ( unsigned i=0; i < bo_vec.size(); i++ )
	{
		const box_object* other_bo = bo_vec.at(i);

		if ( box_in_box( x, y, bo->dimens.w(), bo->dimens.h(), other_bo->dimens.x(), other_bo->dimens.y(), other_bo->dimens.w(), other_bo->dimens.h() ) )
		{
			return false;
		}
	}

	bo->dimens.x(x);
	bo->dimens.y(y);

	return true;
}
