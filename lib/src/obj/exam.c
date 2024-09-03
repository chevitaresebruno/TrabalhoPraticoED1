#include <stdlib.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"

#include "lib/include/obj/exam.h"


struct exam
{
    ID id;
    ID xrm_id;
    ID p_id;
    Condition* cond;
    TM* time;
    int i_time;

    Exam* next;
};


Exam* exam_create(const ID id, const ID xrm_id, const ID p_id, Condition* cond, const TM* tm, const int i_time)
{
    Exam* e;

    if(id == 0 || xrm_id == 0 || p_id == 0 || cond == NULL || tm == NULL)
        return NULL;

    e = (Exam*)malloc(sizeof(Exam));
    if(e == NULL)
        return NULL;
    
    e->time = (TM*)malloc(sizeof(TM));
    if(e->time == NULL)
    {
        free(e);
        return NULL;
    }


    e->id = id;
    e->xrm_id = xrm_id;
    e->p_id = p_id;
    e->cond = cond;
    *(e->time) = *tm;
    e->i_time = i_time;
    e->next = NULL;

    return e;
}


ID exam_get_id(const Exam* e)
{
    if(e == NULL)
        return 0;
    
    return e->id;
}

ID exam_get_xrmid(const Exam* e)
{
    if(e == NULL)
        return 0;
    
    return e->xrm_id;
}

ID exam_get_pid(const Exam* e)
{
    if(e == NULL)
        return 0;
    
    return e->p_id;
}

Condition* exam_get_cond(const Exam* e)
{
    if(e == NULL)
        return NULL;
    
    return e->cond;
}

TM* exam_get_time(const Exam* e)
{
    if(e == NULL)
        return NULL;
    
    return e->time;
}

int exam_get_itime(const Exam* e)
{
    if(e == NULL)
        return -1;
    
    return e->i_time;
}

Exam* exam_get_next(Exam* e)
{
    if(e == NULL)
        return NULL;
    
    return e->next;
}


void exam_set_next(Exam* exam, Exam* next)
{
    if(exam == NULL || next == NULL)
        return;
    
    exam->next = next;
}


void exam_free(Exam* e)
{
    if(e == NULL)
        return;
    
    if(e->cond != NULL)
        cond_free(e->cond);
        
    if(e->time != NULL)
        free(e->time);

    free(e);
}