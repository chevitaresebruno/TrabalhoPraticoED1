#pragma once

/*
    Codes used in patient_free function for better readability.

    Uses:
        - General: when you call function patient_free you must use some of this code, NULL is not a option;
        - DESTROY: means you want to destroy the patient, so all used memory will be free;
        - RETURN_NEXT_AND_DESTROY: means you want to destroy the patient and return the next patient in list;
        - ALLOCATE_NAME_ERROR: it`s used in patient.c, when the patient_create is call and there is no memory to create it`s name, this arg is passed;
        - ALLOCATE_TIMESTAMP_ERROR: it`s used in patient.c, when the patient_create is call and there is no memory to create it`s timestamp, this arg is passed;
*/
enum PATIENT_FREE_CODE {DESTROY, RETURN_NEXT_AND_DESTROY, ALLOCATE_NAME_ERROR, ALLOCATE_TIMESTAMP_ERROR};

/*
    This function free the allocated memory for a patient.
    args:
        patient -> pointer for the patient you want free;
        free_code -> the way you want to free the patient.
    return:
        A pointer to a patient. It`s NULL by default, but if the free_code is RETURN_NEXT_AND_DESTROY it will be patient->next.
*/
Patient* patient_free(Patient* patient, const unsigned char free_code);


/*
    This function create a new patient
    args:
        patient_id -> the patient id in database;
        patient_name -> a pointer to patient name, this argument is copied into the name attribute;
        timestamp -> a pointer to patient timestamp, this argument is copied into the tm attribute.
    return:
        A pointer to the created patient.
*/
Patient* patient_create(const unsigned int patient_id, const char* patient_name, const TM* timestamp);

/*
    This function get a patient id.
    args:
        patient-> a pointer to the patient you want get the id.
    return:
        a new unsigned interger that contains the patient id.
*/
unsigned int patient_get_id(const Patient* patient);

/*
    This function get the patient name pointer.
    args:
        patient -> a pointer to the patient you want to get the the name pointer.
    return:
        A pointer to the patient name.
*/
char* patient_get_name_ptr(const Patient* patient);

/*
    This function get the patient name.
    args:
        patient -> a pointer to the patient you want to get the name.
    return:
        A char pointer that contains a copy of patient name. 
*/
char* patient_get_name(const Patient* patient);

/*
    This function get the patient timestamp pointer.
    args:
        patient -> a pointer to the patient you want to get the the timestamp pointer.
    return:
        A pointer to the patient timestamp.
*/
struct tm* patient_get_timestamp_ptr(const Patient* patient);

/*
    This function get the patient timestamp.
    args:
        patient -> a pointer to the patient you want to get the the timestamp.
    return:
        A struct tm pointer that contains a copy of patient timestamp.
*/
struct tm* patient_get_timestamp(const Patient* patient);

/*
    Get the next patient pointer
    args:
        patient -> a pointer to the patient you want to get the timestamp.
    return:
        A pointer to the next patient in the simple chained list.
*/
Patient* patient_get_next_ptr(const Patient* patient);


/*
    This function set the next attribure from patient as the other argument pass. Atention, the argument origin is now in source->next, it does`t create an origin copy.
 
    args:
        source -> a pointer to patient will recive the other;
        other -> a pointer to patient will be appointed by source.
*/
void patient_set_next(Patient* source, Patient* origin);

/* 
    This function simple return the size of patient struct
    return:
        sizeof(struct patient).
*/
int patient_sizeof();