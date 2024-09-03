#pragma once

/*
    Feature:
        Condition is a struct that represents a patient Condition.

    Attributes:
        char* name -> Pointer to the condition's name; and
        int sev -> A integer to condition severity.
    
    Verbs:
        Create -> Creates a new Condition record;
        Get -> Retrieves an attribute from the Condition structure;
        Free -> Frees the allocated memory for the Condition record.
*/
typedef struct condition Condition;


/*
    Verb: Create
    
    Args:
        const char* name -> Pointer to the first character of the condition's name; and
        const int severity -> A integer may representate condition severity.
    
    Return:
        A pointer to a newly created Condition record. If memory allocation fails, returns NULL.
*/
Condition* cond_create(const char* name, const int severity);


/*
    Verb: Get
    
    Args:
        const Condition* condition -> Pointer to the Condition object from which data is retrieved.
    
    Return:
        A pointer to name of condition record. If argument is NULL, the function may return NULL.
*/
char* cond_get_name(Condition* condition);

/*
    Verb: Get
    
    Args:
        const Condition* condition -> Pointer to the Condition object from which data is retrieved.
    
    Return:
        An integer of condition record sev attribure. If argument is NULL, the function may return -1.
*/
int cond_get_sev(const Condition* condition);


/*
    Verb: Free

    Args:
        Condition* condition -> Pointer to the condition object to be freed.
    
    Description:
        Frees the memory allocated for the Patient record.
*/
void cond_free(Condition* condition);