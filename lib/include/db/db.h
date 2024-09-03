#pragma once

/*
    Feature:
        Creates a folder where database file will be stored.
*/
void db_create_folder();

/*
    Feature:
        Creates a file where patient data will be stored.
*/
void db_create_patient();

/*
    Feature:
        Creates a file where exam data will be stored.
*/
void db_create_exam();

/*
    Feature:
        Creates a file where report data will be stored.
*/
void db_create_report();


/*
    Feature:
        Insert Patient data in repective database file.
    
    Args:
        FILE* open_file -> A pointer to alredy open file (expected the correct database);
        const Patient* patient -> A pointer to Patient object where data will be retrived; and
        const int simulation_time -> The current time in simulation.
*/
void db_insert_patient(FILE* open_file, const Patient* patient, const int simulation_time);

/*
    Feature:
        Insert Exam data in repective database file.
    
    Args:
        FILE* open_file -> A pointer to alredy open file (expected the correct database);
        const Exam* exam -> A pointer to Exam object where data will be retrived; and
        const int simulation_time -> The current time in simulation.
*/
void db_insert_exam(FILE* open_file, const Exam* exam, const int simulation_time);

/*
    Feature:
        Insert Report data in repective database file.
    
    Args:
        FILE* open_file -> A pointer to alredy open file (expected the correct database);
        const Report* report -> A pointer to Report object where data will be retrived; and
        const int simulation_time -> The current time in simulation.
*/
void db_insert_report(FILE* open_file, const Report* report, const int simulation_time);