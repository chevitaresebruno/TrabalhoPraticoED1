#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "patient.h"


Patient* create_patient(int id, char* name, struct tm* birthdate) {
    Patient* p = (Patient*)malloc(sizeof(Patient));

    /*Memory check for exam*/
    if (p == NULL) {
        perror("Failed to allocate memory for new patient");
        exit(EXIT_FAILURE);
    }

    p->id = id;
    p->name = (char*)malloc(sizeof(char)*strlen(name)); /* Allocate memory for a new pointer to maintain the scope (the variable referring to the parameter name will not be altered if p->name is altered).*/
    p->birthdate = (struct tm*)malloc(sizeof(struct tm)); /* Allocate memory for a new pointer to maintain the scope (the variable referring to the parameter birthdate will not be altered if p->birthdate is altered).*/

    /* Memory check for name */
    if (p->name == NULL) {
        perror("Failed to allocate memory for patient name");
        exit(EXIT_FAILURE);
    }

    /* Memory Check for birthdate */
    if (p->birthdate == NULL) {
        perror("Failed to allocate memory for patient birthdate");
        exit(EXIT_FAILURE);
    }

    strcpy(p->name, name);
    *(p->birthdate) = *birthdate;
    
    return p;
}


int get_patient_id(Patient* p) {
    if (p != NULL)
        return p->id;

    return NULL;
}


const char* get_patient_name(Patient* p) {
    if (p != NULL)
        return p->name;
    
    return NULL;
}   


struct tm* get_patient_birthdate(Patient* p) {
    if (p != NULL)
        return p->birthdate;

    return NULL;
}


void destroy_patient(Patient* p) {
    if (p != NULL)
    {
        free(p->name);
        free(p->birthdate);
        free(p);
    }
}
