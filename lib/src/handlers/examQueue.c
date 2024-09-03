#include <stdlib.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"

#include "lib/include/obj/exam.h"

#include "lib/include/handlers/examQueue.h"


struct examQueue
{
    QueueSize size;
    int pn;
    Exam* first;
    Exam** lasts_per_p;
};


ExamQueue* eq_create(const int pn)
{
    ExamQueue* eq;

    eq = (ExamQueue*)malloc(sizeof(ExamQueue));
    if(eq == NULL)
        return NULL;
    

    eq->lasts_per_p = (Exam**)calloc(pn, sizeof(Exam*));
    if(eq->lasts_per_p == NULL)
    {
        free(eq);
        return NULL;
    }

    eq->size = 0;
    eq->pn = pn;
    eq->first = NULL;

    return eq;
}


QueueSize eq_get_size(const ExamQueue* eq)
{
    if(eq == NULL)
        return -1;
        
    return eq->size;
}


void eq_insert(ExamQueue* eq, Exam* e)
{
    register int i;
    
    if(eq == NULL || e == NULL)
        return;

    i = cond_get_sev(exam_get_cond(e));

    if(!eq->size)
    {
        eq->first = e;
        goto END;
    }

    if(eq->lasts_per_p[i] != NULL)
    {
        exam_set_next(e, exam_get_next(eq->lasts_per_p[i]));
        exam_set_next(exam_get_next(eq->lasts_per_p[i]), e);
        goto END;
    }

    for(i++; i < eq->pn; i++)
    {
        Exam* aux;

        aux = eq->lasts_per_p[i];
        if(aux != NULL)
        {
            exam_set_next(exam_get_next(e), exam_get_next(aux));
            exam_set_next(exam_get_next(aux), e);
            i = cond_get_sev(exam_get_cond(e));
            goto END;
        }
    }

    exam_set_next(exam_get_next(e), eq->first);
    eq->first = e;
    i = cond_get_sev(exam_get_cond(e));

    END:
    eq->lasts_per_p[i] = e;
    eq->size++;
}


Exam* eq_remove(ExamQueue* eq)
{
    Exam* e;

    if(eq == NULL || eq->first == NULL)
        return NULL;

    e = eq->first;
    eq->first = exam_get_next(e);

    if(exam_get_next(e) == NULL || cond_get_sev(exam_get_cond(exam_get_next(e))) != cond_get_sev(exam_get_cond(e)))
        eq->lasts_per_p[cond_get_sev(exam_get_cond(e))] = NULL;
    
    eq->size--;
    return e;
}