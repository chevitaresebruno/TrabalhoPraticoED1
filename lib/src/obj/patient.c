#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/obj/patient.h"


struct patient
{
    int id;
    char* name;
    struct tm* time;
    Patient* next;
};


Patient* patient_create(const ID id, const char* name, const TM* time) {
    Patient* p;

    p = (Patient*)malloc(sizeof(Patient));
    if(p == NULL)
        return NULL;
 
    p->name = (char*)malloc(sizeof(char)*strlen(name));
    if(p->name == NULL)
    {
        free(p);
        return NULL;
    }
    
    p->time = (TM*)malloc(sizeof(TM));
    if(p->time == NULL)
    {
        free(p->name);
        free(p);
        return NULL;
    }
    
    p->id = id;
    strcpy(p->name, name);
    *(p->time) = *time;
    p->next = NULL;

    return p;
}


ID patient_get_id(const Patient* p)
{
    if(p == NULL)
        return 0;
    return p->id;
}

char* patient_get_name(const Patient* p)
{
    char* c;
    
    if(p == NULL)
        return NULL;
    
    c = (char*)malloc(sizeof(char)*strlen(p->name));
    if(c == NULL)
        return NULL;

    strcpy(c, p->name);
    return c;
}

TM* patient_get_time(const Patient* p)
{
    TM* t;

    if(p == NULL)
        return NULL;

    t = (TM*)malloc(sizeof(TM));
    if(t == NULL)
        return NULL;
    *t = *(p->time);

    return t;
}

Patient* patient_get_next(const Patient* p)
{
    if(p == NULL)
        return NULL;

    return p->next;
}


void patient_set_next(Patient* p, Patient* n)
{
    if(p == NULL || p == NULL)
        return;

    p->next = n;
}


void patient_free(Patient* p)
{
    if(p == NULL)
        return;
    
    if(p->time != NULL)
        free(p->time);
    if(p->name != NULL)
        free(p->name);
    free(p);
}