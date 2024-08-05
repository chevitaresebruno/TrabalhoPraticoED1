#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/* MACROS */
#define SIMULATION_TIME_UNITS 43200
#define SEED time(NULL)

#define IsNull(value) (value == NULL)
#define IsNotNull(value) (value != NULL)

/* GLOBALS */
enum ERROS {MEMORY_ERROR, UNKNOWN_ERROR};

typedef struct tm TM;

/* PATIENT */
typedef struct patient Patient;

struct patient {
    unsigned int id;
    char* name;
    TM* timestamp;
    Patient* next;
};

enum PATIENT_FREE_CODE {DESTROY, ALLOCATE_NAME_ERROR, ALLOCATE_TIMESTAMP_ERROR};

typedef struct patientQueue PatientQueue;

struct patientQueue {
    unsigned int size;
    Patient* first;
    Patient* last;
};

void free_patient(Patient* p, const unsigned char free_code) {
    switch (free_code)
    {
    case ALLOCATE_NAME_ERROR:
        break;
    
    case ALLOCATE_TIMESTAMP_ERROR:
        free(p->name);
        break;
    case DESTROY:
        free(p->timestamp);
        free(p->name);
    default:
        printf("ATENTIO, THE CODE %d IS NOT IMPLEMENTADED. THE PATIENT HAS NOT BEEN DESTROYED.", free_code);
        return;
    }

    free(p->next);
    free(p);
}

Patient* create_patient(const unsigned int last_patient_id, const char* patient_name, const TM* timestamp) {
    Patient* p = (Patient*)malloc(sizeof(Patient));
    
    if(IsNull(p)) {
        perror("ERROR IN MEMORY ALLOCATION TO NEW PATIENT");
        exit(MEMORY_ERROR);
    }

    p->id = last_patient_id;
    
    p->name = (char*)malloc(sizeof(char)*strlen(patient_name));
    if(IsNull(p->name)) {
        free_patient(p, ALLOCATE_NAME_ERROR);

        perror("ERROR IN MEMORY ALLOCATION TO PATIENT NAME");
        exit(MEMORY_ERROR);
    }

    p->timestamp = (TM*)malloc(sizeof(TM));
    if(IsNull(p->timestamp)) {
        free_patient(p, ALLOCATE_TIMESTAMP_ERROR);

        perror("ERROR IN MEMORY ALLOCATION TO PATIENT TIMESTAMP");
        exit(MEMORY_ERROR);
    }

    strcpy(p->name, patient_name);
    *(p->timestamp) = *timestamp;
    p->next = NULL;


    return p;
}


void free_patient_queue(PatientQueue* pq) {
    Patient* p = pq->first;
    Patient* fp;

    while (IsNotNull(p))
    {
        fp = p;
        p = fp->next;

        free_patient(fp, DESTROY);
    }
    
    free(pq->first);
    free(pq->last);

    free(pq);
}

PatientQueue* create_patient_queue() {
    PatientQueue* pq = (PatientQueue*)malloc(sizeof(PatientQueue));

    if(IsNull(pq)) {
        perror("ERROR IN MEMORY ALLOCATION TO NEW PATIENTE QUEUE");
        exit(MEMORY_ERROR);
    }

    pq->size = 0;
    pq->first = NULL;
    pq->last = NULL;

    return pq;
}

void insert_patient_in_queue(PatientQueue* pq, Patient* p) {
    if (pq->size) {
        if(IsNull(pq->first) || IsNull(pq->last)) {
            perror("ATENTION, SOMETHING WENT WRONG. THE PATIENTE QUEUE CANT'T HAVE JUST FIRST OR LAST ELEMENT WITH POINTER.");
            exit(UNKNOWN_ERROR);
            }
        
        pq->last->next = p;
        pq->last = p;
    }
    else {
        pq->first = p;
        pq->last = p;
    }

    pq->size++;
}

/* EXAM */


/* DATA BASE */
void db_insert(Patient* p) {
    FILE* fptr = fopen("db_patient.txt", "a+");

    fprintf(fptr, "%d %s %d %d %d\n", p->id, p->name, p->timestamp->tm_mday, p->timestamp->tm_mon, p->timestamp->tm_year);

    fclose(fptr);
}

/* SIMULATION */
#define NEW_PATIENT_PROBALY 2
#define NewPatientCome rand()%10 < NEW_PATIENT_PROBALY


void add_patient(PatientQueue* pq) {
    struct tm birthdate = {0}; 
    birthdate.tm_year = 2004; 
    birthdate.tm_mon = 10; 
    birthdate.tm_mday = 8; 


    Patient* p = create_patient(pq->last->id, "NAME", &birthdate);
    insert_patient_in_queue(pq, p);
    db_insert(p);
}

void simulation() {
    register unsigned int i=0;
    PatientQueue* pq = create_patient_queue();
    
    struct tm birthdate = {0}; 
    birthdate.tm_year = 2004; 
    birthdate.tm_mon = 10; 
    birthdate.tm_mday = 8; 
    Patient* p = create_patient(0, "NAME", &birthdate);

    srand(SEED);

    while (!(NewPatientCome))
        i++;

    insert_patient_in_queue(pq, p);
    add_patient(pq);
    
   
    /*
    for(i=0; i<SIMULATION_TIME_UNITS; i++) {
        if(NewPatientCome){
            if(pq->size)
                add_patient(pq);
            else
                insert_patient()
        }
    }
    */

}

/* MAIN */
int main() {

    simulation();

    return 0;
}