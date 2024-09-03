#pragma once

/*
    Feature:
        Patient is a struct that represents a patient record in a database as a Simple Chained List.

    Attributes:
        ID id -> Patient's ID;
        char* name -> Pointer to the patient's name;
        struct tm* time -> Pointer to a struct tm that stores the time the patient arrived at the hospital; and
        Patient* next -> Pointer to the next element in the list.
    
    Verbs:
        Create -> Creates a new Patient record;
        Get -> Retrieves an attribute from the Patient structure;
        Set -> Set an attribute from Patient record; and
        Free -> Frees the allocated memory for the Patient record.
*/
typedef struct patient Patient;


/*
    Verb: Create
    
    Args:
        const ID id -> The patient's ID;
        const char* name -> Pointer to the first character of the patient's name; and
        const TM* time -> Pointer to the time when the patient arrived.
    
    Return:
        A pointer to a newly created Patient record. If memory allocation fails, returns NULL.
*/
Patient* patient_create(const ID id, const char* name, const TM* time);


/*
    Verb: Get
    
    Args:
        const Patient* patient -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The id from Patient record. If argument is NULL, the function may return 0.
*/
ID patient_get_id(const Patient* patient); 

/*
    Verb: Get
    
    Args:
        const Patient* patient -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        A copy name from Patient record. If argument is NULL, or memory allocation fails, the function may return NULL.
*/
char* patient_get_name(const Patient* patient);

/*
    Verb: Get
    
    Args:
        const Patient* patient -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        A copy time from the Patient record. If argument is NULL, or memory allocation fails, the function may return NULL.
*/
TM* patient_get_time(const Patient* patient);

/*
    Verb: Get
    
    Args:
        const Patient* patient -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The next attribute from the Patient record. If argument is NULL, the function may return NULL.
*/
Patient* patient_get_next(const Patient* patient);


/*
    Verb: Set
    
    Args:
        Patient* patient -> Pointer to the Patient object from which attribute is set; and
        Patient* next -> Pointer to the Patient object will be set as next from other argument.
    
    Return:
        A copy time from the Patient record. If argument is NULL, or memory allocation fails, the function may return NULL.
*/
void patient_set_next(Patient* patient, Patient* next);

/*
    Verb: Free

    Args:
        Patient* patient -> Pointer to the Patient object to be freed.
    
    Description:
        Frees the memory allocated for the Patient record.
*/
void patient_free(Patient* patient);

