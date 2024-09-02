#include <stdlib.h>
#include <string.h>

#include "ai.h"


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
        return cond_create("Saude Normal", 0);
    else if(aux < 50)
        return cond_create("Bronquite", 1);
    else if(aux < 60)
        return cond_create("Pneumonia", 2);
    else if(aux < 70)
        return cond_create("COVID", 3);
    else if(aux < 75)
        return cond_create("Embolia Pulmonar", 3);
    else if(aux < 80)
        return cond_create("Derrame Pleural", 3);
    else if(aux < 85)
        return cond_create("Fibrose Pulmonar", 4);
    else if(aux < 90)
        return cond_create("Tuberculose", 4);
    else
        return cond_create("Câncer de pulmão", 5);
}


void cond_free(Condition* c)
{
    if(c == NULL)
        return;
    
    if(c->name != NULL)
        free(c->name);
    free(c);
}