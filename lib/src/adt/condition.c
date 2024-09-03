#include <stdlib.h>
#include <string.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"


struct condition
{
    char* name;
    int sev;
};


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


char* cond_get_name(Condition* c)
{
    if(c == NULL || c->name == NULL)
        return NULL;
    
    return c->name;
}

int cond_get_sev(const Condition* c)
{
    if(c == NULL)
        return -1;
    
    return c->sev;
}


void cond_free(Condition* c)
{
    if(c == NULL)
        return;

    if(c->name != NULL)
        free(c->name);
    free(c);
}
