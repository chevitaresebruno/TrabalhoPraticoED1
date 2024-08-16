/*
    This file is used to create an envoriment.
    Basicly, this code will set much globals variables tha are much usefull in code. Edit the .env file to change it.
    By the way, some Formulas are defined in this to. 
    Use he function set_env_vars to set the envoryment.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* SIMULATION SEED. USED IN main.c */
int SEED;
#define RANDOM_SEED time(NULL)

/* Used in simulation.c file */
unsigned int SIMULATION_TIME_UNITS;
unsigned int NEW_PATIENT_PROBALY;
#define NewPatientCome rand()%100 < NEW_PATIENT_PROBALY

/* Used in db.c file */
char* DATA_BASE_FOLDER; 
char* DATA_BASE_NAME;
char* DATA_BASE_METADATA_FILE;

/* Used in xrmm.c file */
unsigned int XRAY_MACHINE_NUMBER;
unsigned int XRAY_MACHINE_EXAM_TIME_UNIT;

/* Used in ia.c */
#define IA_OUTPUT rand()%100
char* CONDITIONS_FILE_PATH;


void get_seed(int* s) {
    char* seed;
    seed = getenv("SEED");

    *s = seed!="random" ? atoi(seed) : NULL;
}

void set_env_vars() {
    
    get_seed(&SEED);
    SIMULATION_TIME_UNITS = atoi(getenv("SIMULATION_TIME_UNITS"));
    NEW_PATIENT_PROBALY = atoi(getenv("NEW_PATIENT_PROBALY"));
    DATA_BASE_FOLDER = getenv("DATA_BASE_FOLDER");
    DATA_BASE_NAME = getenv("DATA_BASE_NAME");
    DATA_BASE_METADATA_FILE = getenv("DATA_BASE_METADATA_FILE");
    XRAY_MACHINE_NUMBER = atoi(getenv("XRAY_MACHINE_NUMBER"));
    XRAY_MACHINE_EXAM_TIME_UNIT = atoi(getenv("XRAY_MACHINE_EXAM_TIME_UNIT"));
    CONDITIONS_FILE_PATH = getenv("CONDITIONS_FILE_PATH");
}

