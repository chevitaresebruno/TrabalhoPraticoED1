#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/exam/condition.h"
#include "lib/include/exam/exam.h"

#include "lib/include/exam/examQueue.h"

/* Priority Queue */

struct examQueue
{
    Exam* fe; /* First Exam */
    Exam** lepp; /* Last Exam per Priority */
};

void examqueue_free(ExamQueue* eq) {
    Exam* e;
    register int i;

    e = eq->fe;

    while (e)
        e = exam_free(e, E_DESTROY_AND_GET_NEXT);
    
    for(i = 0; i < condition_how_much(); i++)
        free(eq->lepp[i]);
}

ExamQueue* examqueue_create() {
    ExamQueue* eq;

    eq = (ExamQueue*)malloc(sizeof(ExamQueue));
    if(IsNull(eq)) {
        perror("MEMORY ERROR; ALOCATE NEW EXAM_QUEUE");
        exit(MEMORY_ERROR);
    }

    eq->fe = NULL;
    eq->lepp = (Exam**)malloc(exam_sizeof()*condition_how_much());

    if(IsNull(eq->lepp)) {
        printf("ERROR TO ALLOCATE MEMORY TO EXAM");
        exit(MEMORY_ERROR);
    }

    return eq;
}

void examqueue_insert(ExamQueue* eq, Exam* e) {
    Exam* last;
    unsigned char sev;

    sev = condition_get_sev(exam_get_condition_ptr(e));

    assert(IsNull(eq));
    assert(IsNull(e));
    assert(sev <= 0);

    last = eq->lepp[sev-1];
    exam_set_next(last, e);
    eq->lepp[sev-1] = e;
}


Exam* examqueue_remove(ExamQueue* eq) {
    Exam* r;
    Exam* n;

    r = eq->fe;
    n = exam_get_next_ptr(r);

    if(IsNull(n))
        return r;

    exam_set_next(eq->fe, n);
    
    if(condition_get_sev(exam_get_condition_ptr(r)) != condition_get_sev(exam_get_condition_ptr(n)))
        n = NULL;
    
    eq->lepp[condition_get_sev(exam_get_condition_ptr(r)) - 1] = n;   

    return r; 
}

