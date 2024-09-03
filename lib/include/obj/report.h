#pragma once

/*
    Feature:
        Patient is a struct that represents a Report record in a database.

    Attributes:
        ID id -> Report's ID;
        ID e_id -> Exam's ID;
        Bool ai_da -> The artifical inteligence condition was aceptd;
        Condition* cond -> A pointer to condition after pass medic analisys; and
        TM* time -> The time that report has been created;
    
    Verbs:
        Create -> Creates a new Report record;
        Get -> Retrieves an attribute from the Report structure;
        Free -> Frees the allocated memory for the Report record.
*/
typedef struct report Report;

/*
    Verb: Create
    
    Args:
        const ID id -> The report's ID;
        const ID exam_id -> The exam that generate this report;
        Bool artificalInteligence_diagnosysAcepted -> The information if the artifical inteligence dagnosys has ben acceptd;
        Condition* condition -> The condition; and
        const TM* time -> The time tha exam has ben created.
    
    Return:
        A pointer to a newly created Report record. If memory allocation fails, or any argument are invalid (ID equals 0 or any others equals NULL) returns NULL.
*/
Report* report_create(const ID id, const ID exam_id, Bool artificalInteligence_diagnosysAcepted, Condition* condition, const TM* time);


/*
    Verb: Get
    
    Args:
        const Report* report -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The ID from Report record. If argument is NULL, the function may return 0.
*/
ID report_get_id(const Report* report);

/*
    Verb: Get
    
    Args:
        const Report* report -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The Exam ID from Report record. If argument is NULL, the function may return 0.
*/
ID report_get_eid(const Report* report);

/*
    Verb: Get
    
    Args:
        const Report* report -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The ad_da attribute from Report record. If argument is NULL, the function may return Invalid (2).
*/
Bool report_get_aida(const Report* report);


/*
    Verb: Get
    
    Args:
        const Report* report -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The condition from Report record. If argument is NULL, the function may return NULL.
*/
Condition* report_get_cond(const Report* report);

/*
    Verb: Get
    
    Args:
        const Report* report -> Pointer to the Patient object from which data is retrieved.
    
    Return:
        The time from Report record. If argument is NULL, the function may return NULL.
*/
TM* report_get_time(const Report* report);


/*
    Verb: Free

    Args:
        Report* report -> Pointer to the Report object to be freed.
    
    Description:
        Frees the memory allocated for the Report record.
*/
void report_free(Report* report);
