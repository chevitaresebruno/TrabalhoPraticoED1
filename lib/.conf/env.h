/*
    This file is used to define some params in code.
    It culd be an .env file, but i prefer use it as an .h c file for performance and it's easy than configure an env file for the project :p
*/

#pragma once

/* SIMULATION SEED. USED IN main.c */
#define SEED time(NULL)

/* Used in simulation.c file */
#define SIMULATION_TIME_UNITS 43200
#define NEW_PATIENT_PROBALY 20
#define NewPatientCome rand()%100 < NEW_PATIENT_PROBALY
#define XRAY_MACHINES_ID {1, 2, 3, 4, 5}

/* Used in db.c file */
#define DATA_BASE_FOLDER "output" 
#define DATA_BASE_NAME "db_patient"
#define DATA_BASE_METADATA_FILE "db_patient_metadata"

/* Used in xrmm.c file */
#define XRAY_MACHINE_NUMBER 5
#define XRAY_MACHINE_EXAM_TIME_UNIT 10

/* Used in ia.c */
#define IA_OUTPUT rand()%100
#define CONDITIONS_FILE_PATH "lib/.conf/conditions.json"
