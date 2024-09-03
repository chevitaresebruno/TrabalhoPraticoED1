#include <stdlib.h>

#include "lib/include/shared.h"

#include "lib/include/adt/xrmo.h"

#include "lib/include/handlers/xrmm.h"


/*
    Attributes:
        int size -> The number of machines the simulation will have;
        ID* id -> The id of each machine;
        ID* ap_id -> The id of each alocated patient in some machine; and
        int* i_time -> Counts how much iterations in simulation rests to dealloc patient, and is used to check if machine is allocated.
*/
struct xrmm
{
    int size;
    ID* id;
    ID* ap_id;
    int* i_time;
};


XRMachineManager* xrmm_create(const int size, const ID* xrm_ids)
{
    XRMachineManager* xrmm;
    register int i;

    if(!size)
        return NULL;
    
    xrmm = (XRMachineManager*)malloc(sizeof(XRMachineManager));
    if(xrmm == NULL)
        return NULL;

    xrmm->id = (ID*)malloc(sizeof(ID)*size);
    if(xrmm->id == NULL)
    {
        free(xrmm);
        return NULL;
    }

    xrmm->ap_id = (ID*)calloc(size, sizeof(ID));
    if(xrmm->ap_id == NULL)
    {
        free(xrmm->id);
        free(xrmm);
        return NULL;
    }

    xrmm->i_time = (int*)calloc(size, sizeof(int));
    if(xrmm->i_time == NULL)
    {
        free(xrmm->ap_id);
        free(xrmm->id);
        free(xrmm);
        return NULL;
    }

    xrmm->size = size;
    for(i = 0; i < size; i++)
        xrmm->id[i] = xrm_ids[i];

    return xrmm;
}


Bool xrmm_alloc_machine(XRMachineManager* xrmm, const ID p_id)
{
    register int mn;

    if(!p_id || xrmm == NULL)
        return False;

    for(mn = xrmm->size; mn >= 0; mn--)
    {
        if(!xrmm->i_time[mn])
        {
            xrmm->ap_id[mn] = p_id;
            xrmm->i_time[mn] = 10;
            return True;
        }
    }

    return False;
}


/*
    Feature Complements:
        This function delloc machine and time count every machine slots. We prefered use it other create a function to time count to get better performance.
*/
xrMachineOutput* xrmm_dealloc_machie(XRMachineManager* xrmm)
{
    xrMachineOutput* xrmo;
    register int mn;

    xrmo = NULL;
    for(mn = 4; mn >= 0; mn--)
    {
        if(xrmm->i_time[mn])
        {
            xrmm->i_time[mn]--;
            if(!xrmm->i_time[mn])
                xrmo = xrmo_create(xrmm->id[mn], xrmm->ap_id[mn]);
        }
    }

    return xrmo;
}


Bool xrmm_check_isEmpty(const XRMachineManager* xrmm)
{
    register int i;

    for(i=0; i < 5; i++)
        if(xrmm->i_time[i])
            return False;

    return True;
}

