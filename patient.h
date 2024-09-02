#pragma once

/*
    Feature:
        Patient is a struct that represents a patient record in a database as a Simple Chained List.

    Attributes:
        int id -> Patient's ID;
        char* name -> Pointer to the patient's name;
        struct tm* time -> Pointer to a struct tm that stores the time the patient arrived at the hospital; and
        Patient* next -> Pointer to the next element in the list.
    
    Verbs:
        Create -> Creates a new Patient record;
        Get -> Retrieves an attribute from the Patient structure; and
        Free -> Frees the allocated memory for the Patient record.
*/
typedef struct patient Patient;

/*
    Verb: Create
    
    Args:
        const int id -> The patient's ID;
        const char* name -> Pointer to the first character of the patient's name; and
        const struct tm* time -> Pointer to the time when the patient arrived.
    
    Return:
        A pointer to a newly created Patient record. If memory allocation fails, returns NULL.
*/
Patient* patient_create(const int id, const char* name, const struct tm* time);

/*
    Verb: Get
    
    Args:
        const Patient* patient -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The requested attribute from the Patient record. If any argument is NULL, or memory allocation fails, the function may return NULL or an invalid value.
*/

int patient_get_id(const Patient* patient); /* Return Complements: If patient argument is NULL, the function may return 0. */
char* patient_get_name(const Patient* patient);
struct tm* patient_get_time(const Patient* patient);

/*
    Verb: Free

    Args:
        Patient* patient -> Pointer to the Patient object to be freed.
    
    Description:
        Frees the memory allocated for the Patient record.
*/
void patient_free(Patient* patient);


/*
    Feature:
        PatientQueue is a struct that represents a queue of patients operating in a FIFO (First In, First Out) manner.
    
    Attributes:
        All attributes in PatientQueue are private.
    
    Verbs:
        Create -> Creates a new PatientQueue;
        Get -> Retrieves an attribute from the PatientQueue structure;
        Insert -> Inserts a Patient into the queue;
        Remove -> Removes a Patient from the queue; and
        Free -> Frees the allocated memory for the PatientQueue.
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
        The id you want catch. If argument is NULL, the function may return 0.
*/
int pq_get_fisrt_id(PatientQueue* patientQueue);
int pq_get_size(PatientQueue* patientQueue);


/*
    Verb: Insert
    
    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue where data will be inserted; and
        Patient* patient -> Pointer to the Patient to be inserted into the queue.
    
    Attention:
        If any argument is NULL, the function does nothing.
*/
void pq_insert(PatientQueue* patientQueue, Patient* patient);


/*
    Verb: Remove
    
    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue from which a Patient will be removed.
    
    Return:
        A pointer to the removed Patient. Returns NULL if the queue is empty.
*/
Patient* pq_remove(PatientQueue* patientQueue);


/*
    Verb: Remove and Free

    Feature Complement:
        Removes a Patient from the queue and frees its memory. 

    Args:
        PatientQueue* patientQueue -> Pointer to the PatientQueue from which a Patient will be removed and freed.
    
    Description:
        This function removes a Patient from the queue and deallocates the memory used by the Patient record.
*/
void pq_remove_and_free(PatientQueue* patientQueue);
