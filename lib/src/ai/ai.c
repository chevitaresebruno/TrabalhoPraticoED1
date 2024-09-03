#include <stdlib.h>

#include "lib/include/adt/condition.h"

#include "lib/include/ai/ai.h"


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
        return cond_create("Cancer de Pulmao", 5);
}
