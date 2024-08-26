/*
    xrmm = X-Ray Machine Manager
*/

#pragma once


enum XRMM_FREE_CODE {DESTROY, ALLOCATE_PATIENT_ERROR, ALLOCATE_TIME_ERROR, ALLOCATE_MACHINE_ERROR};


void xrmm_free(XRMM* xrmm, unsigned char free_code);


XRMM* xrmm_create(unsigned int machine_number, const unsigned int* machines_id);


void xrmm_time_down(XRMM* xrmm);


BOOL xrmm_alloc_patient(XRMM* xrmm, unsigned int p_id);

XRMM_DeallocOut* xrmm_dealloc_patients(XRMM* xrmm);

unsigned int xrmmDealloOut_get_mid(const XRMM_DeallocOut* xmdo);

unsigned int xrmmDealloOut_get_pid(const XRMM_DeallocOut* xmdo);
