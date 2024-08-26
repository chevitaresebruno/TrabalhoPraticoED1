#pragma once

/*
    Codes used in db_get function for better readability.
    Uses:
        - General -> when you call the function db_get you must use one of this codes, NULL is not a option;
        - ID -> means you want the ID (not implementaded yet);
        - LAST_ID -> means you want kown the last id insert in the database.
*/
enum GET_OPTIONS {ID, LAST_ID};


/*
    This function insert patient info in database. If the database does not exist, it will create a new one.
    args:
        patient -> a pointer to the patient you want to insert in the database.
*/
void db_insert(void* info, const char* database_name);

/*
    This function get something from the database.
    args:
        option -> the GET_OPTIONS you want;
        save -> a pointer to an variabel will save the value get, you must know the elemt type, because the typecast will be made inside the function.
*/
void db_get(unsigned int option, void* save);

/*
    This function checks if it's everything ok with the database. It is used in start of simulation to prevents possible bugs (we dont test everything, so it may happen :p).
*/
void db_check();
