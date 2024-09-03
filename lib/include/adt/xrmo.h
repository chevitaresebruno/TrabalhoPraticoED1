#pragma once

/*
    Feature:
        xrMachineOutput is a struct that represents an output from xrmm_dealloc function, from xrmm.c.

    Attributes:
        ID xrm_id -> The id from X-Ray Machine that made the exam;
        ID p_id -> The Patient who made the exam;
    
    Verbs:
        Create -> Creates a new xrMachineOutput;
        Get -> Retrieves an attribute from the xrMachineOutput structure; and
        Free -> Frees the allocated memory for the xrMachineOutput.
*/
typedef struct xrmo xrMachineOutput;


/*
    Verb: Create
    
    Args:
        const ID xRayMachine_ID -> The ID from X-Ray Mahchine that made the exam; ad
        const ID patient_id -> The ID from Patient that made the exam. 
    
    Return:
        A pointer to a newly created xrMachineOutput. If memory allocation fails, returns NULL.
*/
xrMachineOutput* xrmo_create(const ID xRayMachine_ID, const ID patient_id);

/*
    Verb: Get
    
    Args:
        const xrMachineOutput* xRayMachineOutput -> Pointer to the xrMachineOutput object from which data is retrieved.
    
    Return:
        The X-Ray Machine ID from the xrMachineOutput record. If argument is NULL, the function may return 0.
*/
ID xrmo_get_xrmid(const xrMachineOutput* xRayMachineOutput);

/*
    Verb: Get
    
    Args:
        const xrMachineOutput* xRayMachineOutput -> Pointer to the xrMachineOutput object from which data is retrieved.
    
    Return:
        The Patient ID from the xrMachineOutput record. If argument is NULL, the function may return 0.
*/
ID xrmo_get_pid(const xrMachineOutput* xRayMachineOutput);


/*
    Verb: Free

    Args:
        xrMachineOutput* xRayMachineOutput -> Pointer to the xrMachineOutput object to be freed.
    
    Description:
        Frees the memory allocated for the xrMachineOutput.
*/
void xrmo_free(xrMachineOutput* xRayMachineOutput);
