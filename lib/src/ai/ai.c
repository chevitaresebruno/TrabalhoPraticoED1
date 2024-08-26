#include <stdlib.h>
#include <stdio.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/.extern/cjson/cJSON.h"

#include "lib/include/exam/condition.h"


Condition* ia_output() {
    cJSON* json;
    Condition* cond;
    unsigned int ia_o;
    int i;
    
    json = cJSON_Parse_File(CONDITIONS_FILE_PATH);
    cond = condition_allocate_memory();
    ia_o = IA_OUTPUT;

    for(i=0; i<cJSON_GetArraySize(json); i++)
    {
        cJSON_Parse_Condition(cJSON_GetArrayItem(json, i), cond);
        
        if(ia_o < (condition_get_prob(cond) * 100))
            return cond;
    }
    
    
    printf("ERROR, THE PROBABILITY SUMS IS NOT 1.");
    exit(CONF_ERROR);
}
