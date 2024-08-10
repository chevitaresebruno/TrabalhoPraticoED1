#pragma once

void pq_free(PatientQueue* patient_queue);


PatientQueue* pq_create();


void pq_insert(PatientQueue* patiente_queue, Patient* patient);


Patient* pq_remove(PatientQueue* patient_queue);


unsigned int pq_get_size(const PatientQueue* patient_queue);

Patient* pq_get_patient_ptr(const PatientQueue* patiente_queue, unsigned int index); /* 1 for get the first element */

Patient* pq_get_first_ptr(const PatientQueue* patient_queue);

Patient* pq_get_last_ptr(const PatientQueue* patient_queue);