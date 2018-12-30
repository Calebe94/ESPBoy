#include "sysinit.h"
#include "modules.h"
#include "manager.h"

// TODO: Should have a .h file called managers.h which include all managers, just like modules.h have
#include "battery_manager.h"

err_t os_init(void)
{
    modules_init();

    manager_init();

    return RESP_OK;
}
