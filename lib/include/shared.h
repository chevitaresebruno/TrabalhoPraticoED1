/*
    This file contains a lot of usefull stuffs that`s used in other scripts
*/

#pragma once

#define IsNull(value) (value == NULL)
#define IsNotNull(value) (value != NULL)


typedef struct tm TM;
typedef struct patient Patient;
typedef struct pq PatientQueue;

enum ERROS {MEMORY_ERROR, UNKNOWN_ERROR};