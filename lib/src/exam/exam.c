#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/exam/exam.h"

#include "lib/.extern/cjson/cJSON.h"


struct condition {
    char* name;
    double prob;
    unsigned char sev;
};


Condition* condition_create(const char* name, const double prob, const int sev) {
    Condition* cond;
    
    cond = (Condition*)malloc(sizeof(Condition));
    if(IsNull(cond)) {
        perror("CREATE CONDITION");
        exit(MEMORY_ERROR);
    }

    cond->name = (char*)malloc(sizeof(char)*strlen(name));
    if(IsNull(cond->name)) {
        free(cond);
        perror("CREATE CONDITION NAME");
        exit(MEMORY_ERROR);
    }

    strcpy(cond->name, name);
    cond->prob = prob;
    cond->sev = sev;

    return cond;
}


void cJSON_Parse_Condition(const cJSON* json, Condition* cond) {
    cJSON* name; 
    cJSON* prob; 
    cJSON* sev;

    name = cJSON_GetObjectItem(json, "nome");
    prob = cJSON_GetObjectItem(json, "probabilidade");
    sev = cJSON_GetObjectItem(json, "gravidade");

    if(IsNull(name) || IsNull(prob) || IsNull(sev)) {
        printf("THE JSON OBJECT IS NOT CORRECT");
        exit(UNKNOWN_ERROR);
    }

    if(IsNull(cond))
        cond = condition_create(name->string, prob->valuedouble, sev->valueint);
    else {
        cond->name = name->string;
        cond->prob += prob->valuedouble; /* Specific use to better performance */
        cond->sev = sev->valueint;
    }
}


Condition* ia_output() {
    cJSON* json;
    Condition* cond;
    unsigned int ia_o;
    
    json = cJSON_Parse_File(CONDITIONS_FILE_PATH);
    cond = NULL;
    ia_o = IA_OUTPUT;

    for(register unsigned int i=0; i<cJSON_GetArraySize(json); i++)
    {
        cJSON_Parse_Condition(json, cond);

        if(ia_o < (cond->prob * 100))
            return cond;
    }
    
    
    printf("ERROR, THE PROBABILITY SUMS IS NOT 1.");
    exit(CONF_ERROR);
}