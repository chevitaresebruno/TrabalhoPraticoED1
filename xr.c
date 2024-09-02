#include <stdlib.h>

#include "xr.h"


struct xrMachineManager
{
    int* id; /* int id[] = {1, 2, 3, 4, 5} */
    int* ap_id;
    int* t;
};


/*

*/
xrMachineOutput* xrmo_create(const int xrm_id, const int p_id)
{
    xrMachineOutput* xrmo;

    xrmo = (xrMachineOutput*)malloc(sizeof(xrMachineOutput));
    if(xrmo == NULL)
        return NULL;
    
    xrmo->xrm_id = xrm_id;
    xrmo->p_id = p_id;

    return xrmo;
}


xrMachineManager* xrmm_create(const int size, const int* xrm_ids)
{
    xrMachineManager* xrmm;
    int i;

    if(!size)
        return NULL;
    
    xrmm = (xrMachineManager*)malloc(sizeof(xrMachineManager));
    if(xrmm == NULL)
        return NULL;

    xrmm->id = (int*)malloc(sizeof(int)*size);
    if(xrmm->id == NULL)
    {
        free(xrmm);
        return NULL;
    }

    xrmm->ap_id = (int*)calloc(size, sizeof(int));
    if(xrmm->ap_id == NULL)
    {
        free(xrmm->id);
        free(xrmm);
        return NULL;
    }

    xrmm->t = (int*)calloc(size, sizeof(int));
    if(xrmm->t == NULL)
    {
        free(xrmm->ap_id);
        free(xrmm->id);
        free(xrmm);
        return NULL;
    }

    for(i = 0; i < size; i++)
        xrmm->id[i] = xrm_ids[i];

    return xrmm;
}


int xrmm_alloc_m(xrMachineManager* xrmm, const int p_id)
{
    int mn;

    if(!p_id || xrmm == NULL)
        return 0;

    for(mn = 4; mn >= 0; mn--)
    {
        if(!xrmm->t[mn])
        {
            xrmm->ap_id[mn] = p_id;
            xrmm->t[mn] = 10;
            return 1;
        }
    }

    return 0;
}


xrMachineOutput* xrmm_dealloc_m(xrMachineManager* xrmm)
{
    xrMachineOutput* xrmo;
    register int mn;

    xrmo = NULL;
    for(mn = 4; mn >= 0; mn--)
    {
        if(xrmm->t[mn])
        {
            xrmm->t[mn]--;
            if(!xrmm->t[mn])
                xrmo = xrmo_create(xrmm->id[mn], xrmm->ap_id[mn]);
        }
    }

    return xrmo;
}

int xrmm_is_empty(const xrMachineManager* xrmm)
{
    register int i;

    for(i=0; i < 5; i++)
        if(xrmm->t[i])
            return 0;

    return 1;
}

/* DEBUGGER ROOM */
/*
int main()
{
    int xrm_ids[] = {1, 2, 3, 4, 5};
    xrMachineManager* xrmm = xrmm_create(5, xrm_ids);
    xrMachineOutput* xrmo;
    int i;

    for (i=1; i < 8; i++)
    {   
        if(!xrmm_alloc_m(xrmm, i))
            break;
    }

    for (i=0; i < 20; i++)
    {   
        xrmo = xrmm_dealloc_m(xrmm);
    }

    i = xrmm_alloc_m(xrmm, i);
    i = 5;
    i = xrmm_alloc_m(xrmm, i);
    i = 5;
    i = xrmm_alloc_m(xrmm, i);
    i = 5;
    i = xrmm_alloc_m(xrmm, i);
    i = 5;
    i = xrmm_alloc_m(xrmm, i);
    i = 5;
    i = xrmm_alloc_m(xrmm, i);

    return 0;
}
*/
