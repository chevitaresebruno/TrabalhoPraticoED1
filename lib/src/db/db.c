#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/patient/patient.h"

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <sys/stat.h>  // Biblioteca para funções de diretório em Unix-like
#include <sys/types.h>
#endif


void db_insert(Patient* p) {
    FILE* fptr = fopen("output/db_patient.txt", "a+");

    if(IsNull(fptr)) {
        #if defined(_WIN32) || defined(_WIN64)
        mkdir("output");
        #else
        mkdir("output", 0755);
        #endif
    }

    fptr = fopen("output/db_patient.txt", "a+");

    fprintf(fptr, "%d %s %d %d %d\n", patient_get_id(p), patient_get_name_ptr(p), patient_get_timestamp_ptr(p)->tm_mday, patient_get_timestamp_ptr(p)->tm_mon, patient_get_timestamp_ptr(p)->tm_year);

    fclose(fptr);
}