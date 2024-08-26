/*
    xrmm = X-Ray Machine Manager
    This file contains all important definition for correct work of X-Ray Machines.
*/

#include <stdlib.h>
#include <stdio.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/xray/xrmm.h"


struct xrmm {
    unsigned int size;
    unsigned int* patients;
    unsigned int* time;
    unsigned int* machines;
};


struct xrmm_dealloc_out {
    unsigned int p_id;
    unsigned int m_id;
};


void xrmm_free(XRMM* xrmm, unsigned char free_code) {
    switch (free_code)
    {
    case X_ALLOCATE_PATIENT_ERROR:
        break;
    case X_ALLOCATE_TIME_ERROR:
        free(xrmm->patients);
        break;
    case X_ALLOCATE_MACHINE_ERROR:
        free(xrmm->time);
        free(xrmm->patients);
        break;        
    case X_DESTROY:
        free(xrmm->time);
        free(xrmm->patients);
        free(xrmm->machines);
        break;

    default:
        printf("ATENTION, THE CODE %d IS NOT IMPLEMENTADED", free_code);
        break;
    }

    free(xrmm);
}


XRMM* xrmm_create(unsigned int mn, const unsigned int* ms_id) {
    XRMM* xrmm;
    
    xrmm = (XRMM*)malloc(sizeof(xrmm));
    if(IsNull(xrmm)) {
        perror("CREATE STRUCT XRMM.");
        exit(MEMORY_ERROR);
    }

    xrmm->patients = (unsigned int*)calloc(mn, sizeof(unsigned int));
    if(IsNull(xrmm->patients)) {
        xrmm_free(xrmm, X_ALLOCATE_PATIENT_ERROR);
        perror("ALLOCATE PATIENTS");
        exit(MEMORY_ERROR);
    }

    xrmm->time = (unsigned int*)calloc(mn, sizeof(unsigned int));
    if(IsNull(xrmm->time)) {
        xrmm_free(xrmm, X_ALLOCATE_TIME_ERROR);
        perror("ALLOCATE TIME");
        exit(MEMORY_ERROR);
    }

    xrmm->machines = (unsigned int*)malloc(sizeof(unsigned int)*mn);
    register unsigned int i;
    if(IsNull(xrmm->machines)) {
        xrmm_free(xrmm, X_ALLOCATE_MACHINE_ERROR);
        perror("ALLOCATE MACHINES");
        exit(MEMORY_ERROR);
    }
    for(i = 0; i < mn; i++)
        xrmm->machines[i] = ms_id[i];
    
    xrmm->size = mn;

    return xrmm;
}


void xrmm_time_down(XRMM* xrmm) {
    register unsigned int i;

    for(i = 0; i < xrmm->size; i++) {
        if(xrmm->time[i])
            xrmm->time[i]--;
    }
}


BOOL xrmm_alloc_patient(XRMM* xrmm, unsigned int p_id) {
    register unsigned int i;
    if(!p_id || IsNull(p_id))
        return FALSE;
    
    for(i = 0; i < xrmm->size; i++) {
        if(xrmm->patients[i] == 0) {
            xrmm->patients[i] = p_id;
            xrmm->time[i] = XRAY_MACHINE_EXAM_TIME_UNIT;
            return TRUE;
        }
    }

    return FALSE;
}

XRMM_DeallocOut* xrmm_dealloc_patients(XRMM* xrmm) {
    XRMM_DeallocOut* output;
    register unsigned int i;

    for(i = 0; i < xrmm->size; i++) {
        if((xrmm->time[i] == 0) & (xrmm->patients[i] != 0)) {
            xrmm->patients[i] = 0;
            output = (XRMM_DeallocOut*)malloc(sizeof(XRMM_DeallocOut));
            if(IsNull(output)) {
                perror("NOT ENOGH MEMORY");
                exit(MEMORY_ERROR);
            }

            output->p_id = xrmm->patients[i];
            output->m_id = xrmm->machines[i];
            printf("ENTRAMOS AQUI %u %u", output->p_id, output->m_id);
            return output;
        }
    }

    return NULL;
}


unsigned int xrmmDealloOut_get_mid(const XRMM_DeallocOut* xmdo) {
    return xmdo->m_id;
}

unsigned int xrmmDealloOut_get_pid(const XRMM_DeallocOut* xmdo) {
    return xmdo->p_id;
}