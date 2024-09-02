#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "patient.h"
#include "ai.h"
#include "examQueue.h"
#include "db.h"


void db_create_patient()
{
    FILE* f;

    f = fopen("db_patient.txt", "w");

    fclose(f);
}

void db_create_exam()
{
    FILE* f;

    f = fopen("db_exam.txt", "w");

    fclose(f);
}

void db_create_report()
{
    FILE* f;

    f = fopen("db_report.txt", "w");

    fclose(f);
}


/*
    Feature:
        Just print the struct tm in file.
    Args:
        FILE* f -> A pointer to alredy open file; and
        const struct tm* t -> A pointer to time data.
*/
void db_print_date(FILE* f, const struct tm* t)
{
    fprintf(f, "DATA: %d/%d/%d, HORARIO: %d:%d:%d;\n", t->tm_mday, t->tm_mon, t->tm_year+1900, t->tm_hour, t->tm_min, t->tm_sec);
}


void db_insert_patient(FILE* f, const Patient* p, const int i)
{
    fprintf(f, "ID: %d, NOME: %s, ITERAÇÃO: %d, ", patient_get_id(p), patient_get_name(p), i);
    db_print_date(f, patient_get_time(p));
}

void db_insert_exam(FILE* f, const int id, const int xrm_id, const int p_id, const char* c, const struct tm* time, const int i)
{    
    fprintf(f, "ID: %d, XRAY_MACHINE_ID: %d, PATIENT_ID: %d, CONDITION: %s, ITERACAO: %d, ", id, xrm_id, p_id, c, i);
    db_print_date(f, time);
}

void db_insert_report(FILE* f, const Report* r, int rep_id, struct tm* t, const int i)
{
    char* ia_a;

    if(r==NULL || rep_id==0 || t==NULL)
        return;

    ia_a = r->f_ia? "YES" : "NO";

    fprintf(f, "ID: %d, EXAM_ID: %d, CONDITION: %s, IA_DIAGNOISES_ACCPET: %s, ITERACAO %d, ", rep_id, r->e_id, r->cond->name, ia_a, i);
    db_print_date(f, t);
}


/* DEBUGGER ROOM */
/*
int main()
{
    Patient* p;
    struct tm* t;

    t = (struct tm*)malloc(sizeof(struct tm));

    t->tm_mday = 1;
    t->tm_mon = 1;
    t->tm_year = 1900;
    t->tm_hour = 7;
    t->tm_min = 0;
    t->tm_sec = 0;

    t = (struct tm*)malloc(sizeof(struct tm));
    db_create_patient();

    p = patient_create(1, "PACIENTE1", t);
    db_insert_patient(p);
    p = patient_create(2, "PACIENTE2", t);
    db_insert_patient(p);

    return 0;
}
*/