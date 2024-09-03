#include <stdlib.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"

#include "lib/include/obj/report.h"


struct report
{
    ID id;
    ID e_id;
    Bool ai_da;
    Condition* cond;
    TM* time;
};


Report* report_create(const ID id, const ID e_id, Bool ai_da, Condition* cond, const TM* time)
{
    Report* r;

    if(id == 0 || e_id == 0 || cond == NULL || time == NULL)
        return NULL;
    
    r = (Report*)malloc(sizeof(Report));
    if(r == NULL)
        return NULL;
    
    r->time = (TM*)malloc(sizeof(TM*));
    if(r->time == NULL)
    {
        free(r);
        return NULL;
    }

    r->id = id;
    r->e_id = e_id;
    r->ai_da = ai_da;
    r->cond = cond;
    *(r->time) = *time;

    return r;
}


ID report_get_id(const Report* r)
{
    if(r == NULL)
        return 00;

    return r->id;
}

ID report_get_eid(const Report* r)
{
    if(r == NULL)
        return 0;
    
    return r->e_id;
}

Bool report_get_aida(const Report* r)
{
    if(r == NULL)
        return Invalid;
    
    return r->ai_da;
}

Condition* report_get_cond(const Report* r)
{
    if(r == NULL)
        return NULL;
    
    return r->cond;
}

TM* report_get_time(const Report* r)
{
    if(r == NULL)
        return NULL;
    
    return r->time;
}


void report_free(Report* r)
{
    if(r == NULL)
        return;
    
    if(r->cond != NULL)
        cond_free(r->cond);
    
    if(r->time != NULL)
        free(r->time);
    
    free(r);
}

