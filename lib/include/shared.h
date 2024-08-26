/*
    This file contains a lot of usefull stuffs that`s used in other scripts
*/

#pragma once

#define IsNull(value) (value == NULL)
#define IsNotNull(value) (value != NULL)

typedef enum bool {FALSE, TRUE} BOOL;

typedef struct tm TM;
typedef struct patient Patient;
typedef struct pq PatientQueue;
typedef struct xrmm XRMM;
typedef struct xrmm_dealloc_out XRMM_DeallocOut;
typedef struct condition Condition;
typedef struct exam Exam;
typedef struct examQueue ExamQueue;

enum ERROS {MEMORY_ERROR, UNKNOWN_ERROR, CONF_ERROR};