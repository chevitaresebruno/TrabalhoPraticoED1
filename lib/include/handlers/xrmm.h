#pragma once

/*
    Feature:
        Patient is a struct that handller the machines in simulation.

    Attributes: All attributes in this structer are privates (see xrmm.c).
    
    Verbs:
        Create -> Creates a new xrMachineManager;
        Alloc -> Alloc some patient in machine;
        Dealloc -> Free a machine to new use; and
        Check -> Check's some thing in machines.
*/
typedef struct xrmm xrMachineManager;

/*
    Verb: Create
    
    Args:
        const int size -> Number of machines the simulation will have; and
        xrm_ids -> ID of each machine in simulation.
    
    Return:
        A pointer to a newly created xrMachineManager. If memory allocation fails, returns NULL.
*/
xrMachineManager* xrmm_create(const int size, const ID* xrMachines_ids);


/*
    Verb: Alloc
    
    Args:
        xrMachineManager* xRayMachineManager -> A pointer to machines manager; and
        const ID patient_id -> The id of patient will be allocated in machine.
    
    Return:
        True if can alloc, False othewise. If any argument are invalid (xRayMachineManager equals NULL or patient_id equals 0, the function may return False).
*/
Bool xrmm_alloc_machine(xrMachineManager* xRayMachineManager, const ID patient_id);


/*
    Verb: Dealloc
    
    Args:
        xrMachineManager* xRayMachineManager -> A pointer to machines manager.
    
    Return:
        A new sctructure xrMachineOutput tha contains the machine id and patient id removed.
*/
xrMachineOutput* xrmm_dealloc_machie(xrMachineManager* xRayMachineManager);


/*
    Verb: Check
    
    Args:
        xrMachineManager* xRayMachineManager -> A pointer to machines manager.
    
    Return:
        True (1) if machine is empty, False other wise.
*/
Bool xrmm_check_isEmpty(const xrMachineManager* xRayMachineManager);

