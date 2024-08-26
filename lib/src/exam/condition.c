#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/.extern/cjson/cJSON.h"

#include "lib/include/exam/condition.h"


struct condition {
    char* name;
    double prob;
    unsigned char sev;
};


void condition_free(Condition* cond) {
    free(cond->name);
    free(cond);
}


int condition_how_much() {
    cJSON* json;
    int how_much;

    json = cJSON_Parse_File(CONDITIONS_FILE_PATH);
    how_much = cJSON_GetArraySize(json);
    
    cJSON_Delete(json);
    free(json);

    return how_much;
}


Condition* condition_allocate_memory() {
    Condition* c = (Condition*)malloc(sizeof(Condition));
    
    if(IsNull(c)) {
        perror("CREATE CONDITION");
        exit(MEMORY_ERROR);
    }

    return c;
}


Condition* condition_create(const char* name, const double prob, const int sev) {
    Condition* cond;
    
    cond = condition_allocate_memory();

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

void condition_copy(Condition* dest, const Condition* src) {
    dest = condition_create(src->name, src->prob, src->sev);
}


char* condition_get_name_ptr(Condition* cond) {
    assert(IsNotNull(cond));

    return cond->name;
}

char* condition_get_name(const Condition* cond) {
    char* n;

    assert(IsNotNull(cond));

    n = (char*)malloc(sizeof(char)*strlen(cond->name));
    strcpy(n, cond->name);

    return n;
}

double condition_get_prob(const Condition* cond) {
    assert(IsNotNull(cond));

    return cond->prob;
}

unsigned char condition_get_sev(const Condition* cond) {
    return cond->sev;
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
