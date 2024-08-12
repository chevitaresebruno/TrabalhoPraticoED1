#include <stdlib.h>

#include "lib/.extern/cjson/cJSON.h"

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/exam/condition.h"


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

        if(ia_o < (condition_get_prob(cond) * 100))
            return cond;
    }
    
    
    printf("ERROR, THE PROBABILITY SUMS IS NOT 1.");
    exit(CONF_ERROR);
}
