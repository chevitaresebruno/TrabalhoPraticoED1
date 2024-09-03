#pragma once

/*
    Feature:
        PatientQueue is a struct that represents a queue of patients operating in a FIFO (First In, First Out) manner.
    
    Attributes:
        QueueSize size -> Acutal number of elements in queue;
        Patient* first -> A pointer to first element in queue; and
        Patient* last -> A pointer to last element in queue.
    
    Verbs:
        Create -> Creates a new PatientQueue;
        Get -> Retrieves an attribute from the PatientQueue structure;
        Insert -> Inserts a Patient into the queue; and
        Remove -> Removes a Patient from the queue.
*/
typedef struct patientQueue PatientQueue;


/*
    Verb: Create

    Return:
        A pointer to a newly created PatientQueue. If memory allocation fails, returns NULL.
*/
PatientQueue* pq_create();


/*
    Verb: Get

    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue object from which data is retrieved.
    
    Return:
        The ID of firts element in Queue. If argument is NULL or queue is empty, the function may return 0.
*/
ID pq_get_fisrt_id(PatientQueue* patientQueue);

/*
    Verb: Get

    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue object from which data is retrieved.
    
    Return:
        The size attribute of Queue. If argument is NULL, the function may return -1.
*/
QueueSize pq_get_size(PatientQueue* pq);


/*
    Verb: Insert
    
    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue where data will be inserted; and
        Patient* patient -> Pointer to the Patient to be inserted into the queue.
    
    Return:
        True (1) if operation is sucesfull, or False (0) if any arguments are NULL.
*/
Bool pq_insert(PatientQueue* patientQueue, Patient* patient);


/*
    Verb: Remove
    
    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue from which a Patient will be removed.
    
    Return:
        A pointer to the removed Patient. Returns NULL if the queue is empty.
*/
Patient* pq_remove(PatientQueue* patientQueue);

/*
    Verb: Remove 

    Feature Complement:
        Removes a Patient from the queue and frees its memory. 

    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue from which a Patient will be removed and freed.
    
    Description:
        This function removes a Patient from the queue and deallocates the memory used by the Patient record.
*/
void pq_remove_and_free(PatientQueue* patientQueue);