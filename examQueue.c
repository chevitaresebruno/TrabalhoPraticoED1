#include <stdlib.h>
#include <string.h>

#include "ai.h"
#include "examQueue.h"

struct examQueue
{
    int size;
    int pn;
    Report* first;
    Report** lasts_per_p;
};


Report* report_create(const int id, const int e_id, Condition* cond, const int time)
{
    Report* r;

    r = (Report*)malloc(sizeof(Report));
    if(r == NULL)
        return NULL;
    
    r->cond = cond_create(cond->name, cond->sev);
    if(r->cond == NULL)
    {
        free(r);
        return NULL;
    }

    r->e_id = e_id;
    r->id = id;
    r->f_ia = 1;
    r->time = time;
    r->next = NULL;

    return r;
}

void report_free(Report* r)
{
    if(r == NULL)
        return;
    
    if(r->cond != NULL)
        cond_free(r->cond);
    free(r);
}


ExamQueue* eq_create(const int pn)
{
    ExamQueue* eq;

    eq = (ExamQueue*)malloc(sizeof(ExamQueue));
    if(eq == NULL)
        return NULL;
    

    eq->lasts_per_p = (Report**)calloc(pn, sizeof(Report*));
    if(eq->lasts_per_p == NULL)
    {
        free(eq);
        return NULL;
    }

    eq->first = NULL;
    eq->size = 0;
    eq->pn = pn;

    return eq;
}

void eq_insert(ExamQueue* eq, Report* r)
{
    int i;
    
    i = r->cond->sev;

    if(eq == NULL || r == NULL)
        return;
    
    if(!eq->size)
    {
        eq->first = r;
        goto END;
    }

    if(eq->lasts_per_p[i] != NULL)
    {
        r->next = eq->lasts_per_p[i]->next;
        eq->lasts_per_p[i]->next = r;
        goto END;
    }

    for(i++; i < eq->pn; i++)
    {
        Report* aux;

        aux = eq->lasts_per_p[i];
        if(aux != NULL)
        {
            r->next = aux->next;
            aux->next = r;
            i = r->cond->sev;
            goto END;
        }
    }

    r->next = eq->first;
    eq->first = r;
    i = r->cond->sev;
    
    END:
    eq->lasts_per_p[i] = r;
    eq->size++;
}

Report* eq_remove(ExamQueue* eq)
{
    Report* r;

    if(eq == NULL || eq->first == NULL)
        return NULL;

    r = eq->first;
    eq->first = r->next;
    
    if(r->next == NULL || r->next->cond->sev != r->cond->sev)
        eq->lasts_per_p[r->cond->sev] = NULL;
    
    eq->size--;
    return r;
}

int eq_get_size(const ExamQueue* eq)
{
    return eq->size;
}


/* DEBUGGER ROOM */
/* ai.c */
/*
Condition* cond_create(const char* name, const int sev)
{
    Condition* c;

    c = (Condition*)malloc(sizeof(Condition));
    if(c == NULL)
        return NULL;
    
    c->name = (char*)malloc(sizeof(char)*strlen(name));
    if(c->name == NULL)
    {
        free(c);
        return NULL;
    }
    strcpy(c->name, name);
    c->sev = sev;

    return c;
}


Condition* cond_define()
{
    int aux;

    aux = rand()%100;

    if(aux < 30)
        return cond_create("Saude Normal", 1);
    else if(aux < 50)
        return cond_create("Bronquite", 2);
    else if(aux < 60)
        return cond_create("Pneumonia", 3);
    else if(aux < 70)
        return cond_create("COVID", 4);
    else if(aux < 75)
        return cond_create("Embolia Pulmonar", 4);
    else if(aux < 80)
        return cond_create("Derrame Pleural", 4);
    else if(aux < 85)
        return cond_create("Fibrose Pulmonar", 5);
    else if(aux < 90)
        return cond_create("Tuberculose", 5);
    else
        return cond_create("Câncer de pulmão", 6);
}


void cond_free(Condition* c)
{
    if(c == NULL)
        return;
    
    if(c->name != NULL)
        free(c->name);
    free(c);
}


#include <stdio.h>

int main()
{
    ExamQueue* eq;
    Report* r;
    Condition* c;
    int i;

    eq = eq_create(6);
    for(i = 0; i < 6; i++)
    {
        c = cond_define();
        c->sev = i;
        r = report_create(1, 1, c);
        eq_insert(eq, r);
    }

    for(i = 0; i < 6; i++)
    {
        c = cond_define();
        c->sev = i;
        r = report_create(1, 1, c);
        eq_insert(eq, r);
    }

    for(i=12; i > 0; i--)
    {
        r = eq_remove(eq);
    }
    

    return 0;
}
*/

