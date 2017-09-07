#include "manager.h"

int main()
{
	manager::instance()->init();
	manager::instance()->main_loop();

	return 0;
}
