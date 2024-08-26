#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"
#include "lib/include/patient/patienteQueue.h"
#include "lib/include/db/db.h"
#include "lib/include/xray/xrmm.h"
#include "lib/include/ai/ai.h"
#include "lib/include/exam/condition.h"
#include "lib/include/exam/exam.h"
#include "lib/include/exam/examQueue.h"
#include "lib/include/simulation/simulation.h"


TM* get_current_time() {
    time_t t;
    TM* tw;

    time(&t);
    tw = localtime(&t);

    return tw;
}


void add_patient(PatientQueue* pq, const unsigned int id) {
    Patient* p;
    
    p = patient_create(id, "NAME", get_current_time());

    pq_insert(pq, p);
    db_insert(p, DATA_BASE_NAME);
}

XRMM* create_xrmm() {
    XRMM* xrmm;
    int machines_id[] = XRAY_MACHINES_ID;

    xrmm = xrmm_create(XRAY_MACHINE_NUMBER, machines_id);

    return xrmm;
}

unsigned int first_patient_id(const PatientQueue* pq) {
    if(pq_get_size(pq))
        return patient_get_id(pq_get_first_ptr(pq));
    
    return 0;
}


void simulation() {
    register unsigned int i;

    unsigned int id;
    XRMM_DeallocOut* xrmm_output;
    unsigned int exam_id;

    PatientQueue* pq;
    XRMM* xrmm;
    ExamQueue* eq;

    srand(SEED);
    db_check();

    db_get(LAST_ID, &id);
    pq = pq_create();
    xrmm = create_xrmm();
    eq = examqueue_create();

    for(i=0; i<SIMULATION_TIME_UNITS; i++) {
        if(NewPatientCome) {
            id++;
            add_patient(pq, id);
        }

        if (xrmm_alloc_patient(xrmm, first_patient_id(pq)))
            pq_remove_free(pq);

        xrmm_time_down(xrmm);
        xrmm_output = xrmm_dealloc_patients(xrmm); 
        if(IsNotNull(xrmm_output)) {
            Exam* e;
            Condition* c = ia_output();
            

            e = exam_create(exam_id, xrmmDealloOut_get_mid(xrmm_output), xrmmDealloOut_get_pid(xrmm_output), c, get_current_time());
            printf("1");
            
            if(exam_get_condition_ptr(e) == NULL) {
                printf("SDKJLANDKJLSANLKJDNASKLJ");
            }

            db_insert(e, DATA_BASE_EXAM_NAME);
            printf("1");

            examqueue_insert(eq, e);
            printf("1");
        }

        /* Analisys by Medic */
        /* REPORT */              
    }
}
