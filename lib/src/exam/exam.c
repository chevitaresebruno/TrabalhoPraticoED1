#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/exam/condition.h"
#include "lib/include/exam/exam.h"


struct exam
{
    unsigned int id;
    unsigned int xr_id;
    unsigned int p_id;
    Condition* cond;
    TM* timestamp;
    Exam* next;
};


Exam* exam_free(Exam* e, unsigned char free_code) {
    Exam* n;

    n = NULL;

    switch (free_code)
    {
    case E_ALLOCATE_CONDITION_ERROR:
        break;
    case E_ALLOCATE_TIMESTAMP_ERROR:
        free(e->cond);
        break;
    case E_DESTROY_AND_GET_NEXT:
        n = e->next;
        /* Fall Trough */
    case E_DESTROY:
        free(e->cond);
        free(e->timestamp);
        return n;
    default:
        printf("ATENTION, THE CODE %u IS NOT IMPLEMENTADED. NOTHING HAPPENS TO STRUCT", free_code);
        return NULL;
    }

    free(e);

    return n;
}


Exam* exam_create(const unsigned int id, const unsigned int xr_id, const unsigned int p_id, const Condition* cond, const TM* timestamp) {
    Exam* e;

    e = (Exam*)malloc(sizeof(Exam));
    if(IsNull(e)) {
        perror("CREATE EXAM");
        exit(MEMORY_ERROR);
    }

    e->timestamp = (TM*)malloc(sizeof(TM));
    if(IsNull(e->timestamp)) {
        exam_free(e, E_ALLOCATE_TIMESTAMP_ERROR);
        perror("CREATE TIMESTAMP");
        exit(MEMORY_ERROR);
    }

    e->id = id;
    e->xr_id = xr_id;
    e->p_id = p_id;
    e->cond = condition_create(condition_get_name(cond), condition_get_prob(cond), condition_get_sev(cond));

    if(IsNull(e->cond)) printf("156020200005184804808");
    *(e->timestamp) = *timestamp;

    return e;
}


unsigned int exam_get_id(const Exam* e) {
    return e->id;
}

unsigned int exam_get_xrid(const Exam* e) {
    return e->xr_id;
}

unsigned int exam_get_pid(const Exam* e) {
    return e->p_id;
}

Condition* exam_get_condition_ptr(const Exam* e) {
    return e->cond;
}

TM* exam_get_tm_ptr(const Exam* e) {
    return e->timestamp;
}

Exam* exam_get_next_ptr(const Exam* e) {
    return e->next;
}


void exam_set_next(Exam* dest, Exam* src) {
    dest->next = src;
}

int exam_sizeof() {
    return sizeof(Exam);
}