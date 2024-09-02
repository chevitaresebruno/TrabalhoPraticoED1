#pragma once

typedef struct xrMachineManager xrMachineManager;
typedef struct xrMachineOutput xrMachineOutput;

struct xrMachineOutput
{
    int xrm_id;
    int p_id;
};

xrMachineManager* xrmm_create(const int size, const int* xrm_ids);
int xrmm_alloc_m(xrMachineManager* xrmm, const int p_id);
xrMachineOutput* xrmm_dealloc_m(xrMachineManager* xrmm);
int xrmm_is_empty(const xrMachineManager* xrmm);
