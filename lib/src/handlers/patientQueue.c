#include <stdlib.h>

#include "lib/include/shared.h"

#include "lib/include/obj/patient.h"

#include "lib/include/handlers/patientQueue.h"


struct patientQueue
{
    QueueSize size;
    Patient* first;
    Patient* last;
};


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


ID pq_get_fisrt_id(PatientQueue* pq)
{
    if(pq == NULL || pq->first == NULL)
        return 0;
    
    return patient_get_id(pq->first);
}

QueueSize pq_get_size(PatientQueue* pq)
{
    if(pq == NULL)
        return -1;
        
    return pq->size;
}


Bool pq_insert(PatientQueue* pq, Patient* p)
{
    if(pq==NULL || p==NULL)
        return False;

    if(pq->size)
        patient_set_next(pq->last, p);
    else
        pq->first = p;

    pq->last = p;
    
    pq->size++;

    return True;
}


Patient* pq_remove(PatientQueue* pq)
{
    Patient* p;

    if(pq == NULL || !pq->size)
        return NULL;

    p = pq->first;

    pq->first = patient_get_next(p);
    if(pq->first == NULL)
        pq->last = NULL;
    
    pq->size--;

    return p;
}

void pq_remove_and_free(PatientQueue* pq)
{
    patient_free(pq_remove(pq));
}