/*
    This file is used to define some params in code.
    It culd be an .env file, but i prefer use it as an .h c file for performance and it's easy than configure an env file for the project :p
*/

#pragma once

/* Used in simulation.c file */
#define SIMULATION_TIME_UNITS 43200
#define SEED time(NULL)

#define NEW_PATIENT_PROBALY 20
#define NewPatientCome rand()%100 < NEW_PATIENT_PROBALY

/* Used in db.c file */
#define DATA_BASE_FOLDER "output" 
#define DATA_BASE_NAME "db_patient"
#define DATA_BASE_METADATA_FILE "db_patient_metadata"