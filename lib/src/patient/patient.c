#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"

/* PATIENT */
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
        printf("ATENTION, THE CODE %d IS NOT IMPLEMENTADED. THE PATIENT HAS NOT BEEN DESTROYED.", free_code);
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


int patient_sizeof() {
    return sizeof(Patient);
}
