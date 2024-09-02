#pragma once

/*
    Feature:
        This function create the db_patient.txt file.
*/
void db_create_patient();

/*
    Feature:
        This function create the db_exam.txt file.
*/
void db_create_exam();

/*
    Feature:
        This function create the db_report.txt file.
*/
void db_create_report();

/*
    Feature:
        Insert patient data in db_patient.txt file.
    
    Args:
        Patient* patient -> Pointer to Patient you want extract data an insert in db_patient.txt file.
*/
void db_insert_patient(FILE* f, const Patient* patient, const int i);

/*
    Feature:
        Insert exam data in db_exam.txt file.
    
    Args:
        const int id -> Exam ID;
        const int xrm_id -> Xray machine ID;
        const int p_id -> Patient ID;
        const char* condition_name -> Name of condition; and
        cont struct tm* time -> Time of exam create.
*/
void db_insert_exam(FILE* f, const int id, const int xrm_id, const int p_id, const char* condition_name, const struct tm* time, const int i);

/*

*/
void db_insert_report(FILE* f, const Report* report, int rep_id, struct tm* t, const int i);
