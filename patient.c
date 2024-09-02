/*
    patient.c

    The functions bellow and structures are explainsed in patient.c
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "patient.h"


struct patient
{
    int id;
    char* name;
    struct tm* time;
    Patient* next;
};

struct patientQueue
{
    int size;
    Patient* first;
    Patient* last;
};


/* Patient Features */
Patient* patient_create(const int id, const char* name, const struct tm* time) {
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
    
    p->time = (struct tm*)malloc(sizeof(struct tm));
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


int patient_get_id(const Patient* p)
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

struct tm* patient_get_time(const Patient* p)
{
    struct tm* t;

    if(p == NULL)
        return NULL;

    t = (struct tm*)malloc(sizeof(struct tm));
    if(t == NULL)
        return NULL;
    *t = *(p->time);

    return t;
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


/* Patient Queue Features */
PatientQueue* pq_create()
{
    PatientQueue* pq;

    pq = (PatientQueue*)malloc(sizeof(PatientQueue));
    if(pq == NULL)
        return NULL;
    
    pq->size = 0;
    pq->first = NULL;
    pq->last = NULL;

    return pq;
}


void pq_insert(PatientQueue* pq, Patient* p)
{
    if(pq==NULL || p==NULL)
        return;

    if(pq->size)
        pq->last->next = p;
    else
        pq->first = p;

    pq->last = p;
    
    pq->size++;
}


Patient* pq_remove(PatientQueue* pq)
{
    Patient* p;

    if(pq == NULL || !pq->size)
        return NULL;

    p = pq->first;

    pq->first = p->next;
    if(pq->first == NULL)
        pq->last = NULL;
    
    pq->size--;

    return p;
}

void pq_remove_and_free(PatientQueue* pq)
{
    patient_free(pq_remove(pq));
}


int pq_get_fisrt_id(PatientQueue* pq)
{
    if(pq == NULL || pq->first == NULL)
        return 0;
    
    return pq->first->id;
}

int pq_get_size(PatientQueue* pq)
{
    if(pq == NULL)
        return 0;
        
    return pq->size;
}

/* DEBUGGER ROOM */
/*
#include <stdio.h>

int main() {
    PatientQueue* pq;
    Patient* p;
    int i;

    pq = pq_create();

    printf("INSERINDO VALORES\n");
    for(i = 1; i < 6; i++)
    {
        struct tm* time;

        time = (struct tm*)malloc(sizeof(struct tm));
        time->tm_mday = 1;
        time->tm_mon = 1;
        time->tm_year = 1900;

        p = patient_create(i, "NOME", time);
        pq_insert(pq, p);
    }

    printf("Pacientes Inseridos\n");
    for (p = pq->first; p; p = p->next)
        printf("%d  %s  %d-%d-%d\n", p->id, p->name, p->time->tm_mday, p->time->tm_mon, p->time->tm_year);
    

    printf("Removendo Pacientes\n");
    for(; i > 1; i--)
    {
        pq_remove_and_free(pq);
    }

    printf("\n");

    return 0;
}
*/

