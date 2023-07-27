#include "dctl_plugin.h"
#include <dlfcn.h>

DCTL_getParam_t DCTL_getParam;
DCTL_transform_t DCTL_transform;

bool DCTL_loadPlugin(const char* path)
{
    void *dl_handle = dlopen(path, RTLD_NOW);
    if (dl_handle)
    {
        DCTL_getParam = (DCTL_getParam_t)dlsym(dl_handle, "DCTL_getParam");
        DCTL_transform = (DCTL_transform_t)dlsym(dl_handle, "DCTL_transform");
        if (DCTL_getParam && DCTL_transform)
        {
            return true;
        }
    }
    return false;
}
