#pragma once

#define DATA_BASE_NAME "db_patient"
#define DATA_BASE_FOLDER "output" 

enum GET_OPTIONS {ID, LAST_ID};

void db_insert(struct patient* patient);
void db_get(unsigned int option, void* save);