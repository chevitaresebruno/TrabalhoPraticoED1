#pragma once

/*
    This function free the allocated memory of all queue elements and it self.
    args:
        patient_queue -> the queue ou want to free
*/
void pq_free(PatientQueue* patient_queue);


/*
    This function creates a patient queue.

    return:
        A pointer to created patiente queue
*/
PatientQueue* pq_create();


/*
    This function insert a ptiente in queue.
    args:
        patiente_queue -> a pointer for the queue that function will insert patient;
        patient -> a pointer for the patient will be insertd in the queue, it doesen't creates a patient copy.
*/
void pq_insert(PatientQueue* patiente_queue, Patient* patient);


/*
    This function remove the first patient from queue.
    args:
        patient_queue -> the queue that will have a patient remove.
    return:
        A pointer to the removed patient.
*/
Patient* pq_remove(PatientQueue* patient_queue);

/*
    This function remove the first patient from queue and free it.
    args:
        patient_queue -> the queue that will have a patient remove.
*/
void pq_remove_free(PatientQueue* pq);

/*
    This function get the queue size.
    args:
        patient_queue -> the queue you want know the size.
    return:
        A unsigned int that representate the queue size.
*/
unsigned int pq_get_size(const PatientQueue* patient_queue);

/*
    This function get the patient pointer by index in queue.
    args:
        patient_queue -> a pointer to the queue you want know a patient;
        index -> a integer that representates the index where the patient is in queue, it must be lower than the queue size.
    return:
        A pointer to the patient at that index.
*/
Patient* pq_get_patient_ptr(const PatientQueue* patiente_queue, unsigned int index); /* 1 for get the first element */

/*
    This function get the first patient in queue.
    args:
        patient_queue -> a pointer to queue you want get the first patient
    return:
        A pointer to the firts patient, it doesen`t creates a copy.
*/
Patient* pq_get_first_ptr(const PatientQueue* patient_queue);

/*
    This function get the last patient in queue.
    args:
        patient_queue -> a pointer to the queue you want to get the last patient.
    return:
        A pointer to the last patient, it doesen`t creates a copy.
*/
Patient* pq_get_last_ptr(const PatientQueue* patient_queue);