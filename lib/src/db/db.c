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
#include "lib/include/exam/exam.h"
#include "lib/include/exam/condition.h"
#include "lib/include/db/db.h"

/* The code creates a directory, so it will check if you is in unix or windows OS. */
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif


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

void db_create_dir() {
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
    This function is private in lib. It creates a new medata file based in a prefetch name. If the database not exist, it will create a fodler and will create the detabase and database metadata files. It`s names can be set in the env.h file. 
*/
BOOL md_create(const BOOL ovwt) {
    FILE* f;
    char* mdn;

    mdn = db_fname(DATA_BASE_METADATA_FILE);

    f = fopen(mdn, "r");

    if(IsNull(f))
        db_create_dir();
    
    else {
        printf("\nATENTION! The metadata alredy exists.");
        if(ovwt) {
            md_restart();
            printf(" The metadata file has been restarted.\n");
            return TRUE;
        }
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
        md_create(FALSE);
        f = fopen(db_fname(DATA_BASE_METADATA_FILE), "w");
    }

    fprintf(f, "-- %u\n", lid);
}

/*
    This function is private in lib. It creates a new databased based in a prefetch name. If the database not exist, it will create a fodler and will create the detabase and database metadata files. It`s names can be set in the env.h file. 
*/
BOOL db_create(const char* db_name) {
    FILE* f;
    char* dbn;

    dbn = db_fname(db_name);

    f = fopen(dbn, "r");

    if(IsNull(f))
        db_create_dir();
    else {
        printf("ATENTION! The database alredy exists");
        return FALSE;
    }

    fclose(f);
    return TRUE;
}

/* Explained in db.h */
void db_insert(void* info, const char* db_name) {
    FILE* f;
    TM* t;

    if(strcmp(DATA_BASE_NAME, db_name))
    {
        info = (Patient*) info;

        f = fopen(db_fname(DATA_BASE_METADATA_FILE), "r");
        if(IsNull(f))
            md_create(FALSE);
        fclose(f);

        md_update_lastid(patient_get_id(info));

        f = fopen(db_fname(db_name), "a");
        if(IsNull(f)) {
            db_create(db_name);
            f = fopen(db_fname(db_name), "a");
        }

        t = patient_get_timestamp_ptr(info);
        fprintf(f, "%d %s - %d %d %d - %d:%d:%d\n", patient_get_id(info), patient_get_name_ptr(info), t->tm_mday, t->tm_mon, t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);

        fclose(f);
        return;
    }

    f = fopen(db_fname(db_name), "a");
    if(IsNull(f)) {
        db_create(db_name);
        f = fopen(db_fname(db_name), "a");
    }

    if(strcmp(DATA_BASE_EXAM_NAME, db_name)) {
        info = (Exam*) info;
        t = exam_get_tm_ptr(info);

        fprintf(f, "%d %d %d %s %d %s %d - %d:%d:%d\n", exam_get_id(info), exam_get_xrid(info), exam_get_pid(info), condition_get_name(exam_get_condition_ptr(info)), t->tm_mday, t->tm_mon, t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
    }
    else if(strcmp(DATA_BASE_REPORT_NAME, db_name)) {

    }


    fclose(f);
}

/* Explained in db.h */
void db_get_last_id(unsigned int* s) {
    FILE* f;
    char line[30];

    f = fopen(db_fname(DATA_BASE_METADATA_FILE), "r");
    if(IsNull(f)) {
        db_create(DATA_BASE_NAME);
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
void db_check() {
    db_create_dir();

    md_create(db_create(DATA_BASE_NAME));  /* The db_create function creates the database DATA_BASE_NAME and returns a BOOL. So, if it creates a new database, the md_create function will overite the metadata file if its alredy exist. Else, it will not. */

    db_create(DATA_BASE_EXAM_NAME);
    db_create(DATA_BASE_REPORT_NAME);
}

