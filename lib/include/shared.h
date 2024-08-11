/*
    This file contains a lot of usefull stuffs that`s used in other scripts
*/

#pragma once

#define IsNull(value) (value == NULL)
#define IsNotNull(value) (value != NULL)

enum BOLL {FALSE, TRUE};

typedef struct tm TM;
typedef struct patient Patient;
typedef struct pq PatientQueue;
typedef struct xrmm XRMM;
typedef struct condition Condition;

enum ERROS {MEMORY_ERROR, UNKNOWN_ERROR, CONF_ERROR};