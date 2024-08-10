#pragma once

enum PATIENT_FREE_CODE {DESTROY, RETURN_NEXT_AND_DESTROY, ALLOCATE_NAME_ERROR, ALLOCATE_TIMESTAMP_ERROR};


Patient* patient_free(Patient* patient, const unsigned char free_code);


Patient* patient_create(const unsigned int patient_id, const char* patient_name, const struct tm* timestamp);


unsigned int patient_get_id(const Patient* patient);

char* patient_get_name_ptr(const Patient* patient);

char* patient_get_name(const Patient* patient);

struct tm* patient_get_timestamp_ptr(const Patient* patient);

struct tm* patient_get_timestamp(const Patient* patient);

Patient* patient_get_next_ptr(const Patient* patient);


void patient_set_next(Patient* source, Patient* origin);


int patient_sizeof();