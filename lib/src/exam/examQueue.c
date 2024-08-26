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

    e = eq->fe;

    while (e)
        e = exam_free(e, DESTROY_AND_GET_NEXT);
    
    for(register unsigned int i = 0; i < condition_how_much(); i++)
        free(eq->lepp[i]);
}

ExamQueue* examqueue_create() {
    ExamQueue* eq;

    eq->fe = NULL;
    eq->lepp = (Exam**)malloc(exam_sizeof()*condition_how_much());

    if(IsNull(eq->lepp)) {
        printf("ERROR TO ALLOCATE MEMORY TO EXAM");
        exit(MEMORY_ERROR);
    }

    return eq;
}

void examqueue_insert(ExamQueue* eq, const Exam* e, const int p) {
    Exam* last;

    assert(IsNull(eq));
    assert(IsNull(e));
    assert(p <= 0);

    last = eq->lepp[p-1];
    exam_set_next(last, e);
    eq->lepp = e;
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

