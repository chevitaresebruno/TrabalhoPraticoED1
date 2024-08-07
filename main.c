#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/db/db.h"
#include "lib/include/patient/patient.h"
#include "lib/include/patient/patienteQueue.h"

/* MACROS */
#define SIMULATION_TIME_UNITS 43200
#define SEED time(NULL)

/* SIMULATION */
#define NEW_PATIENT_PROBALY 2
#define NewPatientCome rand()%10 < NEW_PATIENT_PROBALY


void add_patient(PatientQueue* pq) {
    struct tm birthdate = {0}; 
    birthdate.tm_year = 2004; 
    birthdate.tm_mon = 10; 
    birthdate.tm_mday = 8; 

    Patient* p = patient_create(patient_get_id(pq_get_last_ptr(pq)), "NAME", &birthdate);
    pq_insert(pq, p);
    db_insert(p);
}

void simulation() {
    register unsigned int i=0;
    PatientQueue* pq = pq_create();
    
    struct tm birthdate = {0}; 
    birthdate.tm_year = 2004; 
    birthdate.tm_mon = 10; 
    birthdate.tm_mday = 8; 
    Patient* p = patient_create(0, "NAME", &birthdate);

    srand(SEED);
    
    pq_insert(pq, p);
    add_patient(pq);
    
   
    /*
    for(i=0; i<SIMULATION_TIME_UNITS; i++) {
        if(NewPatientCome){
            if(pq->size)
                add_patient(pq);
            else
                pq_insert()
        }
    }
    */

}

/* MAIN */
int main() {

    simulation();

    return 0;
}