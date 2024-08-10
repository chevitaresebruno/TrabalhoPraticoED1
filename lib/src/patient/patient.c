/*
    This file contains all important definition for correct work of patient struct. All functions in this script are explained in patient.h file.
*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"

/*
    The struct patient representate a patient in a hospital. Patient is a simply chained list.
    attr:
        id -> the id in database;
        name -> a pointer to it`s name;
        tm -> Time and day it`s arrived at the hospital;
        next -> a pointer to the next patient in queue.
*/
struct patient {
    unsigned int id;
    char* name;
    TM* tm;
    Patient* next;
};


Patient* patient_free(Patient* p, const unsigned char free_code) {
    Patient* n;

    if(IsNull(p))
        return NULL;
        
    n = NULL;
    
    switch (free_code)
    {
    case ALLOCATE_NAME_ERROR:
        break;
    
    case ALLOCATE_TIMESTAMP_ERROR:
        free(p->name);
        break;

    case RETURN_NEXT_AND_DESTROY:
        n = p->next;
        /* Fall trough */
    
    case DESTROY:
        free(p->tm);
        free(p->name);
        break;
    
    default:
        /* The only accepted codes are listed in patient.h. If any unexpected code is entered, the patient does not move, and the entered code is returned as an error message*/
        printf("ATENTION, THE CODE %d IS NOT IMPLEMENTADED. THE PATIENT DOES NOT MOVE.", free_code);
        return n;
    }

    free(p);

    return n;
}


Patient* patient_create(const unsigned int p_id, const char* p_name, const TM* timestamp) {
    Patient* p;
    
    p = (Patient*)malloc(sizeof(Patient));
    if(IsNull(p)) {
        perror("CREATE PATIENT: ");
        exit(MEMORY_ERROR);
    }
    
    p->name = (char*)malloc(sizeof(char)*strlen(p_name));
    if(IsNull(p->name)) {
        patient_free(p, ALLOCATE_NAME_ERROR);
        
        perror("CREATE PATIENT NAME");
        exit(MEMORY_ERROR);
    }

    p->tm = (TM*)malloc(sizeof(TM));
    if(IsNull(p->tm)) {
        patient_free(p, ALLOCATE_TIMESTAMP_ERROR);

        perror("CREATE PATIENT TIMESTAMP");
        exit(MEMORY_ERROR);
    }

    p->id = p_id;
    strcpy(p->name, p_name);
    *(p->tm) = *timestamp;
    p->next = NULL;


    return p;
}


/* The functions below only can be used if it's args are not null */
unsigned int patient_get_id(const Patient* p) {
    assert(IsNotNull(p));

    return p->id;
}

char* patient_get_name_ptr(const Patient* p) {
    assert(IsNotNull(p));
    
    return p->name;
}

char* patient_get_name(const Patient* p) {
    char* n;
    
    assert(IsNotNull(p));
    
    n = (char*)malloc(sizeof(char)*strlen(p->name));
    if(IsNull(n)) {
        perror("CREATE COPY OF PATIENT NAME.");
        exit(MEMORY_ERROR);
    }
    strcpy(n, p->name);

    return n;
}

TM* patient_get_timestamp_ptr(const Patient* p) {
    assert(IsNotNull(p));
    
    return p->tm;
}

TM* patient_get_timestamp(const Patient* p) {
    TM* t;

    assert(IsNotNull(p));
    
    t = (TM*)malloc(sizeof(TM));
    if (IsNull(t)) {
        printf("ERROR TO CREATE PATIENT TIMESTAMP COPY");
        exit(MEMORY_ERROR);
    }

    *t = *(p->tm);

    return t; 
}

Patient* patient_get_next_ptr(const Patient* p) {
    assert(IsNotNull(p));
    
    return p->next;
}


void patient_set_next(Patient* src, Patient* ori) {
    assert(IsNotNull(src));
    assert(IsNull(ori));
    
    src->next = ori;
}
/* The functions above only can be used if the args are not null */


int patient_sizeof() {
    return sizeof(Patient);
}
