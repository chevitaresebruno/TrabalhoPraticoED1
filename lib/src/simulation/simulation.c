#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"
#include "lib/include/patient/patienteQueue.h"
#include "lib/include/db/db.h"
#include "lib/include/xray/xrmm.h"
#include "lib/include/simulation/simulation.h"


TM* get_current_time() {
    time_t t;

    time(&t);
    return localtime(t);
}


void add_patient(PatientQueue* pq, const unsigned int id) {
    Patient* p;
    
    p = patient_create(id, "NAME", get_current_time());

    pq_insert(pq, p);
    db_insert(p);
}

XRMM* create_xrmm() {
    int machines_id[] = XRAY_MACHINES_ID;

    return xrmm_create(XRAY_MACHINE_NUMBER, machines_id);
}

unsigned int first_patient_id(const PatientQueue* pq) {
    return patient_get_id(pq_get_first_ptr(pq));
}


void simulation() {
    register unsigned int i;

    unsigned int id;
    unsigned int patient_exam_id;
    unsigned int exam_id;

    PatientQueue* pq;
    XRMM* xrmm;

    db_get(LAST_ID, &id);
    pq = pq_create();
    xrmm = create_xrmm();
    
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
        patient_exam_id = xrmm_dealloc_patients(xrmm); 
        if(patient_exam_id) {
            /* IA OUTPUT */
            /*INSERT IN DB */
            /* INSERT IN PRIORITY QUEUE */

            patient_exam_id = 0;
        }

        /* REPORT */              
    }
}
