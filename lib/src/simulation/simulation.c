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
    tw = localtime(t);

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
    return patient_get_id(pq_get_first_ptr(pq));
}


void simulation() {
    register unsigned int i;

    unsigned int id;
    XRMM_DeallocOut* xrmm_output;
    unsigned int exam_id;

    PatientQueue* pq;
    XRMM* xrmm;
    ExamQueue* eq;

    db_get(LAST_ID, &id);
    pq = pq_create();
    xrmm = create_xrmm();
    eq = examqueue_create();
    
    srand(SEED);
    db_check();
    
    for(i=0; i<SIMULATION_TIME_UNITS; i++) {
        if(NewPatientCome) {
            add_patient(pq, id);
            id++;
        }

        if (xrmm_alloc_patient(xrmm, first_patient_id(pq))) {
            pq_remove(pq);
        }

        xrmm_time_down(xrmm);
        xrmm_output = xrmm_dealloc_patients(xrmm); 
        if(IsNotNull(xrmm_output)) {
            Exam* e;

            e = exam_create(exam_id, xrmmDealloOut_get_mid(xrmm_output), xrmmDealloOut_get_pid(xrmm_output), ia_output(), get_current_time());

            db_insert(e, DATA_BASE_EXAM_NAME);

            examqueue_insert(eq, e);
        }

        /* Analisys by Medic */
        /* REPORT */              
    }
}
