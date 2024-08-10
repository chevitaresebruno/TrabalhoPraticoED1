#pragma once

enum GET_OPTIONS {ID, LAST_ID};

void db_insert(struct patient* patient);
void db_get(unsigned int option, void* save);