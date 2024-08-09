#pragma once

#define SIMULATION_TIME_UNITS 43200
#define SEED time(NULL)

#define NEW_PATIENT_PROBALY 2

void add_patient(PatientQueue* patient_queue);
void simulation();