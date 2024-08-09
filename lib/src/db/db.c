#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"
#include "lib/include/db/db.h"


#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <sys/stat.h>  // Biblioteca para funções de diretório em Unix-like
#include <sys/types.h>
#endif


char* db_name() {
    int db_name_size = strlen(DATA_BASE_FOLDER) + strlen(DATA_BASE_NAME) + 5; /* +5 = "/.txt" */
    char* n = (char*)malloc(sizeof(char)*db_name_size);

    return n;
}

void db_create(FILE* f, const char* flag) {
    char* dbn = db_name();

    f = fopen(dbn, "r");

    if(IsNull(f)) {
        #if defined(_WIN32) || defined(_WIN64)
        mkdir(DATA_BASE_FOLDER);
        #else
        mkdir(DATA_BASE_FOLDER, 0755)
        #endif
    
        f = fopen(dbn, "a+");
        
        fprintf(f, "-- 0\n");
    }
    else
        printf("ATENTION! The database alredy exists");

    fclose(f);

    f = IsNull(flag) ? NULL : fopen(dbn, flag);
}

void db_insert(Patient* p) {
    FILE* f = fopen(db_name(), "w+");
    unsigned int lid;
    char line[30];

    if(IsNull(f))
        db_create(f, "w+");

    fgets(line, sizeof(line), f);
    sscanf(line, "-- %u", &lid);
    lid++;
    fprintf(f, "-- %u", lid);
    fclose(f);

    f = fopen(db_name(), "a");
    fprintf(f, "%d %s %d %d %d\n", patient_get_id(p), patient_get_name_ptr(p), patient_get_timestamp_ptr(p)->tm_mday, patient_get_timestamp_ptr(p)->tm_mon, patient_get_timestamp_ptr(p)->tm_year);

    fclose(f);
}

void db_get_last_id(unsigned int* s) {
    FILE* f = fopen(db_name(), "r");
    char line[30];

    if(IsNull(f)) {
        db_create(f, NULL);
        *s = 0;
        return;
    }

    fgets(line, sizeof(line), f);
    sscanf(line, "-- %u", s);
    
    fclose(f);
}

void db_get(unsigned int option, void* save) {
    switch (option)
    {
    case ID:
        /* code */
        break;
    case LAST_ID:
        db_get_last_id((unsigned int*)save);
        return;

    default:
        perror("CODE NOT IMPLEMENTADED");
        break;
    }
}