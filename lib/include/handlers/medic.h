#pragma once

/*
    Feature:
        Medic is a struct used to handlle exams and reports in simulation.

    Attributes:
        int i_time -> The internal time associated with simulation loop;
        Exam* exam -> Pointer to an Exam object analisys by medic.

    Verbs:
        Create -> Creates a new Medic record;
        Get -> Retrieves attributes from the Medic structure;
        Alloc -> Allocates an exam to the medic;
        Dealloc -> Dealloc an exam to medic analisys;
        CheckIsEmpty -> Checks if the medic has an empty status.
*/
typedef struct medic Medic;


/*
    Verb: Create

    Return:
        A pointer to a newly created Medic record. If memory allocation fails, returns NULL.
*/
Medic* medic_create();


/*
    Verb: Get

    Args:
        Medic* medic -> Pointer to the Medic object from which data is retrieved.

    Return:
        The internal time of the Medic. Returns -1 if the Medic pointer is NULL.
*/
int medic_get_itime(Medic* medic);

/*
    Verb: Get

    Args:
        const Medic* medic -> Pointer to the Medic object from which data is retrieved.

    Return:
        Pointer to the Exam object assigned to the Medic. Returns NULL if the Medic pointer is NULL.
*/
Exam* medic_get_exam(const Medic* medic);


/*
    Verb: Alloc

    Args:
        Medic* m -> Pointer to the Medic object to be allocated;
        Exam* e -> Pointer to the Exam object to be analisys by Medic.

    Description:
        Allocates an exam to the medic and sets the internal time to 30. If any argument is NULL, the function does nothing.
*/
void medic_alloc(Medic* medic, Exam* exam);


/*
    Verb: Dealloc

    Args:
        Medic* m -> Pointer to the Medic object to be deallocated.

    Return:
        A boolean value indicating if the internal time has reached zero after decrementing. Returns False if the Medic pointer is NULL or internal time is already zero.
*/
Bool medic_dealloc(Medic* m);


/*
    Verb: CheckIsEmpty

    Args:
        Medic* m -> Pointer to the Medic object to check.

    Return:
        A boolean value indicating if the internal time is zero. Returns False if the Medic pointer is NULL or internal time is not zero.
*/
Bool medic_check_isEmpty(Medic* m);

