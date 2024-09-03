#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"

#include "lib/include/obj/patient.h"
#include "lib/include/obj/exam.h"
#include "lib/include/obj/report.h"

#include "lib/include/db/db.h"

#ifdef _WIN32 || _WIN64
#include <direct.h>

#define MAKEDIR(dir_name) _mkdir(dir_name)

#else
#include <sys/stat.h>
#include <sys/types.h>

#define MAKEDIR(dir_name) mkdir(dir_name, 0755)

#endif

void db_create_folder()
{
    MAKEDIR("output");
}

void db_create_patient()
{
    FILE* f;

    f = fopen("output/db_patient.txt", "w");

    fclose(f);
}

void db_create_exam()
{
    FILE* f;

    f = fopen("output/db_exam.txt", "w");

    fclose(f);
}

void db_create_report()
{
    FILE* f;

    f = fopen("output/db_report.txt", "w");

    fclose(f);
}


/*
    Feature:
        Just print the TM in file.
    Args:
        FILE* f -> A pointer to alredy open file; and
        const TM* t -> A pointer to time data.
*/
void db_print_date(FILE* f, const TM* t)
{
    fprintf(f, "DATA: %d/%d/%d, HORARIO: %d:%d:%d;\n", t->tm_mday, t->tm_mon, t->tm_year+1900, t->tm_hour, t->tm_min, t->tm_sec);
}


void db_insert_patient(FILE* f, const Patient* p, const int i)
{
    if(f == NULL || p == NULL)
        return;

    fprintf(f, "ID: %d, NOME: %s, ITERAÇÃO: %d, ", patient_get_id(p), patient_get_name(p), i);
    db_print_date(f, patient_get_time(p));
}

void db_insert_exam(FILE* f, const Exam* e, const int i)
{    
    if(f == NULL || e == NULL)
        return;

    fprintf(f, "ID: %d, XRAY_MACHINE_ID: %d, PATIENT_ID: %d, CONDITION: %s, ITERACAO: %d, ", exam_get_id(e), exam_get_xrmid(e), exam_get_pid(e), cond_get_name(exam_get_cond(e)), i);
    db_print_date(f, exam_get_time(e));
}

void db_insert_report(FILE* f, const Report* r, const int i)
{
    char* ia_a;

    if(f == NULL || r == NULL)
        return;

    ia_a = report_get_aida(r)? "YES" : "NO";

    fprintf(f, "ID: %d, EXAM_ID: %d, CONDITION: %s, IA_DIAGNOISES_ACCPET: %s, ITERACAO %d, ", report_get_id(r), report_get_eid(r), cond_get_name(report_get_cond(r)), ia_a, i);
    db_print_date(f, report_get_time(r));
}

