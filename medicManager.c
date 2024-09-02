#include <stdlib.h>
#include <string.h>

#include "ai.h"
#include "examQueue.h"
#include "medicManager.h"


struct medic
{
    int t;
    Report* r;
};


Medic* medic_create()
{
    Medic* m;

    m = (Medic*)malloc(sizeof(Medic));
    if(m == NULL)
        return NULL;
    
    m->t = 0;
    m->r = NULL;

    return m;
}


int medic_alloc(Medic* m, ExamQueue* eq)
{
    if(m==NULL || eq==NULL || !eq_get_size(eq) || m->t)
        return 0;
    
    m->t = 30;

    m->r = eq_remove(eq);

    return 1;
}


int medic_dealloc(Medic* c)
{
    if(c == NULL || !c->t)
        return 0;

    c->t--;

    return !c->t;
}


Report* medic_report(Medic* m)
{
    Condition* c;
    
    if(m == NULL)
        return NULL;

    if(rand()%100 < 80)
        return m->r;
    

    do
        c = cond_define();
    while (!strcmp(c->name, m->r->cond->name));
    
    
    m->r->cond = c;
    m->r->f_ia = 0;

    return m->r;
}

int medic_get_time(Medic* m)
{
    return m->t;
}

Report* medic_get_report(const Medic* m)
{
    return m->r;
}

/* DEBUGGER ROOM */
/*
int main()
{
    Medic* m;
    ExamQueue* eq;

    eq = eq_create(6);
    eq_insert(eq, report_create(0, 0, cond_define()));

    m = medic_create();

    medic_alloc(m, eq_remove(eq));
    if(medic_dealloc(m));
    ;

    return 0;
}
*/

