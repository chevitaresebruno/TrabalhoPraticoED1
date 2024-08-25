/*
    This file contains all important definition for correct work of database (it`s a .txt file :p).
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/.conf/env.h"
#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"
#include "lib/include/db/db.h"

/* The code creates a directory, so it will check if you is in unix or windows OS. */
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif


void create_db_dir() {
    FILE* f;

    #if defined(_WIN32) || defined(_WIN64)
    mkdir(DATA_BASE_FOLDER);
    #else
    mkdir(DATA_BASE_FOLDER, 0755)
    #endif
    
    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "a+");
    fprintf(f, "-- 0\n");
}


/*
    This function is private in the lib. It is a name biulder. The database is inside a folder for better organization, so the script should construct the complete files path. So, if the databse folder is "DB" and the database name is "DB.txt", this function will create it`s full path "DB/DB.txt".

    args:
        fname -> a pointer to file name you wante create.
    return:
        A pointer to full file path.
*/
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


/*
    This function is private in lib. It creates a new medata file based in a prefetch name. If the database not exist, it will create a fodler and will create the detabase and database metadata files. It`s names can be set in the env.h file. 
*/
BOOL md_create() {
    FILE* f;
    char* mdn;

    mdn = db_fname(DATA_BASE_METADATA_FILE);

    f = fopen(mdn, "r");

    if(IsNull(f))
        create_db_dir();
    
    else{
        printf("\nATENTION! The metadata alredy exists");
        return FALSE;
    }

    fclose(f);

    return TRUE;
}


/*
    This function is private in lib. It update the metadata file size attribute. This attribute contains the last patient id insertd.
    args:
        lid -> the value to update the attribute.
*/
void md_update_lastid(unsigned int lid) {
    FILE* f;
    
    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "w");
    if(IsNull(f)) {
        md_create();
        f = fopen(db_fname(DATA_BASE_METADATA_FILE), "w");
    }

    fprintf(f, "-- %u\n", lid);
}

/*

*/
BOOL md_restart() {
    FILE* f;

    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "w+");

    if(IsNull(f))
        return FALSE;
    
    else {
        fclose(f);
        return TRUE;
    }
}

/*
    This function is private in lib. It creates a new databased based in a prefetch name. If the database not exist, it will create a fodler and will create the detabase and database metadata files. It`s names can be set in the env.h file. 
*/
BOOL db_create() {
    FILE* f;
    char* dbn;

    dbn = db_fname(DATA_BASE_NAME);

    f = fopen(dbn, "r");

    if(IsNull(f))
        create_db_dir();
    else {
        printf("ATENTION! The database alredy exists");
        return FALSE;
    }

    fclose(f);
    return TRUE;
}

/* Explained in db.h */
void db_insert(Patient* p) {
    FILE* f;

    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "r");
    if(IsNull(f))
        md_create();
    fclose(f);
    
    md_update_lastid(patient_get_id(p));

    f = fopen(db_fname(DATA_BASE_NAME), "a");
    if(IsNull(f)) {
        db_create();
        f = fopen(db_fname(DATA_BASE_NAME), "a");
    }

    fprintf(f, "%d %s %d %d %d\n", patient_get_id(p), patient_get_name_ptr(p), patient_get_timestamp_ptr(p)->tm_mday, patient_get_timestamp_ptr(p)->tm_mon, patient_get_timestamp_ptr(p)->tm_year);

    fclose(f);
}

/* Explained in db.h */
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

/* Explained in db.h */
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

/* Extern Check */
BOOL folder_exists() {
    struct stat statbuf;


    if (stat(&DATA_BASE_FOLDER, &statbuf) != 0)
        return FALSE;

    return S_ISDIR(statbuf.st_mode); /* TRUE if it is a dir */
}

DB_OUTPUTS_CHECKS db_check() {
    if(!folder_exists()) {
        create_db_dir();
        db_create();
        md_create();

        return FULL_CREATE;
    }
    
    if(db_create()) {
        md_restart();
        return CREATE_DATABASE_AND_RESTART_METADATA_FILE;
    }

    if(md_create())
        return CREATE_METADATA_FILE;
    
    return EVERY_THING_CORRECT;
}

