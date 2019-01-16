#include "sysinit.h"
#include "modules.h"
#include "../daemon/daemon_init.h"
#include "sys_apps.h"

err_t os_init(void)
{
    // Init Kernel modules
    modules_init();

    // Load the managers
    manager_init();

    // Init the System APPS
    // system_apps_init();

    return RESP_OK;
}
