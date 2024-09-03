#include <stdlib.h>

#include "lib/include/shared.h"

#include "lib/include/adt/xrmo.h"


struct xrmo
{
    ID xrm_id;
    ID p_id;
};


xrMachineOutput* xrmo_create(const ID xrm_id, const ID p_id)
{
    xrMachineOutput* xrmo;

    xrmo = (xrMachineOutput*)malloc(sizeof(xrMachineOutput));
    if(xrmo == NULL)
        return NULL;
    
    xrmo->xrm_id = xrm_id;
    xrmo->p_id = p_id;

    return xrmo;
}


ID xrmo_get_xrmid(const xrMachineOutput* xrmo)
{
    if(xrmo == NULL)
        return 0;
    
    return xrmo->xrm_id;
}

ID xrmo_get_pid(const xrMachineOutput* xrmo)
{
    if(xrmo == NULL)
        return 0;
    
    return xrmo->p_id;
}


void xrmo_free(xrMachineOutput* xrmo)
{
    if(xrmo != NULL)
        free(xrmo);
}

