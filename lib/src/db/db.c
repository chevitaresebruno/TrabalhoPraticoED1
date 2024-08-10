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


char* db_fname(const char* fname) {
    int db_name_size; 
    char* n;
 
    db_name_size = strlen(DATA_BASE_FOLDER) + strlen(fname) + 5; /* the formula is DATA_BASE_FOLDER macro length plus fiel you want (fname) length plus 1 from / (DATA_BASE_FOLDER/DATA_BASE_NAME) plus 4 from extension ".txt", so it's +5 = "/.txt" */
    n = (char*)malloc(sizeof(char)*db_name_size);

    strcpy(n, DATA_BASE_FOLDER);
    strcat(n, "/");
    strcat(n, fname);
    strcat(n, ".txt");

    return n;
}

void db_create() {
    FILE* f;
    char* dbn;

    dbn = db_fname(DATA_BASE_NAME);

    f = fopen(dbn, "r");

    if(IsNull(f)) {
        #if defined(_WIN32) || defined(_WIN64)
        mkdir(DATA_BASE_FOLDER);
        #else
        mkdir(DATA_BASE_FOLDER, 0755)
        #endif
        
        f = fopen(db_fname(DATA_BASE_METADATA_FILE), "a+");
        fprintf(f, "-- 0\n");
        fclose(f);
        f = fopen(dbn, "w+");
    }
    else
        printf("ATENTION! The database alredy exists");

    fclose(f);
}

void db_insert(Patient* p) {
    FILE* f;
    char line[30];
    unsigned int id;

    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "r");
    if(IsNull(f)) {
        db_create();
        f = fopen(db_fname(DATA_BASE_METADATA_FILE), "w");
        fprintf(f, "-- %u\n", patient_get_id(p));
    }
    else {
        sscanf(line, "-- %u\n", &id);
        fclose(f);
        f = fopen(db_fname(DATA_BASE_METADATA_FILE), "w");
        id++;
        fprintf(f, "-- %u", id);
    }

    fclose(f);

    f = fopen(db_fname(DATA_BASE_NAME), "a");
    if(IsNull(f)) {
        printf("SOMETHING WENT WORG");
        exit(UNKNOWN_ERROR);
    }

    fprintf(f, "%d %s %d %d %d\n", patient_get_id(p), patient_get_name_ptr(p), patient_get_timestamp_ptr(p)->tm_mday, patient_get_timestamp_ptr(p)->tm_mon, patient_get_timestamp_ptr(p)->tm_year);

    fclose(f);
}

void db_get_last_id(unsigned int* s) {
    FILE* f;
    char line[30];

    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "r");
    if(IsNull(f)) {
        db_create();
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