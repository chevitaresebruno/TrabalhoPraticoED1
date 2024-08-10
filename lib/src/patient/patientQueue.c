#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"
#include "lib/include/patient/patienteQueue.h"


struct pq {
    unsigned int size;
    Patient* first;
    Patient* last;
};


void pq_free(PatientQueue* pq) {
    Patient* p;

    assert(IsNull(pq));

    p = pq->first;

    while (IsNotNull(p))
        p = patient_free(p, RETURN_NEXT_AND_DESTROY);
    
    if(IsNotNull(pq->last)) {
        unsigned int j = 0;
        p = pq->last;
        while (IsNotNull(p)){
            p = patient_free(p, RETURN_NEXT_AND_DESTROY);
            j++;
        }
        
        printf("\n\nALERT! FOR SOME REASON, THE LIST IS BROKEN. \nThe last element of the list found from the first element recorded in the structure does not match the last element recorded in the structure. The last recorded element in the list was linked with %d more elements.", j);
    }

    free(pq);
}


PatientQueue* pq_create() {
    PatientQueue* pq;
    
    pq = (PatientQueue*)malloc(sizeof(PatientQueue));

    if(IsNull(pq)) {
        perror("NEW PATIENTE QUEUE: ");
        exit(MEMORY_ERROR);
    }

    pq->size = 0;
    pq->first = NULL;
    pq->last = NULL;

    return pq;
}


void pq_insert(PatientQueue* pq, Patient* p) {
    assert(IsNotNull(pq));
    assert(IsNotNull(p));

    if (pq->size) {
        if(IsNull(pq->first) && IsNotNull(pq->last)) {
            perror("ATENTION, SOMETHING WENT WRONG. THE PATIENTE QUEUE CANT'T HAVE THE LAST ELEMENT WITH POINTER AND THE FIRST NOT.");
            exit(UNKNOWN_ERROR);
            }

        patient_set_next(pq->last, patient_get_next_ptr(p));
        pq->last = p;
    }

    else {
        pq->first = p;
        pq->last = p;
    }

    pq->size++;
}


Patient* pq_remove(PatientQueue* pq) {
    Patient* p;

    assert(IsNotNull(pq));

    p = pq->first;

    pq->size--;
    patient_set_next(pq->first, patient_get_next_ptr(p));

    return p;
}


unsigned int pq_get_size(const PatientQueue* pq) {
    assert(IsNotNull(pq));

    return pq->size;
}

Patient* pq_get_patient_ptr(const PatientQueue* pq, unsigned int i) {
    Patient* p;
    
    assert(i==0);

    p = pq->first;
    i--;

    while(i--)
        patient_set_next(p, patient_get_next_ptr(p));

    return p;
}

Patient* pq_get_first_ptr(const PatientQueue* pq) {
    assert(IsNotNull(pq));

    return pq->first;
}

Patient* pq_get_last_ptr(const PatientQueue* pq) {
    assert(IsNotNull(pq));

    return pq->last;
}
