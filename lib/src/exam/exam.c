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
};


void exam_free(Exam* e, unsigned char free_code) {
    switch (free_code)
    {
    case ALLOCATE_CONDITION_ERROR:
        break;
    case ALLOCATE_TIMESTAMP_ERROR:
        free(e->cond);
    case DESTROY:
        free(e->cond);
        free(e->timestamp);
    default:
        printf("ATENTION, THE CODE %u IS NOT IMPLEMENTADED. NOTHING HAPPENS TO STRUCT", free_code);
        return;
    }

    free(e);
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
        exam_free(e, ALLOCATE_TIMESTAMP_ERROR);
        perror("CREATE TIMESTAMP");
        exit(MEMORY_ERROR);
    }

    e->id = id;
    e->xr_id = xr_id;
    e->p_id = p_id;
    condition_copy(e->cond, cond);
    *(e->timestamp) = *timestamp;
}
