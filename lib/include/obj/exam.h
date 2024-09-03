#pragma once

/*
    Feature:
        Exam is a struct that represents a Exam record in a database as a Simple Chained List.

    Attributes:
        ID id -> Exam's ID;
        ID xrm_id -> XRayMachine ID that made the exam;
        ID p_id -> Patient's ID who made the exam;
        Condition* cond -> Exam condition result;
        TM* time -> Time the exam had been made;
        int i_time -> The iteration time the exam has been created; and
        
        Exam* next -> A pointer to next Exam in queue.
    
    Verbs:
        Create -> Creates a new Exam record;
        Get -> Retrieves an attribute from the Exam structure;
        Set -> Set an attribute from Exam record; and
        Free -> Frees the allocated memory for the Exam record.
*/
typedef struct exam Exam;


/*
    Verb: Create
    
    Args:
        const ID id -> The exam's ID;
        const ID xRayMachine_id -> The X-Ray Machine that create the exam;
        const ID patient_id -> The patient that mades the exam;
        Condition* condition -> The condition from exam;
        const TM* time -> The time exam has been made; and
        const int i_time -> The simulation iteration time the exam has been created.
    
    Return:
        A pointer to a newly created Exam record. If memory allocation fails or some argument are invalid (ID equals 0 or ADT's NULL), the function may returns NULL.
*/
Exam* exam_create(const ID id, const ID xRayMachine_id, const ID patient_id, Condition* condition, const TM* time, const int iteration_time);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The ID from Exam record. If argument is NULL, the function may return 0.
*/
ID exam_get_id(const Exam* exam);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The X-Ray Machine ID from Exam record. If argument is NULL, the function may return 0.
*/
ID exam_get_xrmid(const Exam* exam);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The Patient ID from Exam record. If argument is NULL, the function may return 0.
*/
ID exam_get_pid(const Exam* exam);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The Condition from Exam record. If argument is NULL, the function may return NULL.
*/
Condition* exam_get_cond(const Exam* exam);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The Time from Exam record. If argument is NULL, the function may return NULL.
*/
TM* exam_get_time(const Exam* exam);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The iteration time from Exam record. If argument is NULL, the function may return NULL.
*/
int exam_get_itime(const Exam* exam);

/*
    Verb: Get
    
    Args:
        const Exam* exam -> Pointer to the Exam object from which data is retrieved.
    
    Return:
        The next exam attribute from Exam record. If argument is NULL, the function may return NULL.
*/
Exam* exam_get_next(Exam* exam);


/*
    Verb: Set
    
    Args:
        Exam* Exam -> Pointer to the Exam object from which attribute is set; and
        Exam* next -> Pointer to the Exam object will be set as next from other argument.
    
    Return:
        A copy time from the Patient record. If argument is NULL, or memory allocation fails, the function may return NULL.
*/
void exam_set_next(Exam* exam, Exam* next);


/*
    Verb: Free

    Args:
        Exam* exam -> Pointer to the exam object to be freed.
    
    Description:
        Frees the memory allocated for the Exam record.
*/
void exam_free(Exam* exam);
