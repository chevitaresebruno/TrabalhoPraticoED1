#include <stdlib.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"

#include "lib/include/obj/exam.h"

#include "lib/include/handlers/medic.h"


struct medic
{
    int i_time;
    Exam* exam;
};


Medic* medic_create()
{
    Medic* m;

    m = (Medic*)malloc(sizeof(Medic));
    if(m == NULL)
        return NULL;
    
    m->i_time = 0;
    m->exam = NULL;

    return m;
}


int medic_get_itime(Medic* m)
{
    if(m == NULL)
        return -1;

    return m->i_time;
}

Exam* medic_get_exam(const Medic* m)
{
    if(m == NULL)
        return NULL;

    return m->exam;
}

void medic_alloc(Medic* m, Exam* e)
{
    if(m == NULL || e == NULL)
        return;
    
    m->i_time = 30;

    m->exam = e;
}


Bool medic_dealloc(Medic* m)
{
    if(m == NULL || !m->i_time)
        return False;

    m->i_time--;

    return !(m->i_time); /*equals m->i_time == 0 ? True : False;*/
}


Bool medic_check_isEmpty(Medic* m)
{
    if(m == NULL || m->i_time)
        return False;
    
    return True;
}

