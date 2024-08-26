#pragma once


int condition_how_much();

Condition* condition_allocate_memory();

Condition* condition_create(const char* name, const double prob, const int sev);

void condition_copy(Condition* dest, const Condition* src);


double condition_get_prob(const Condition* condition);

void cJSON_Parse_Condition(const cJSON* json, Condition* condition);


char* condition_get_name(const Condition* condition);

unsigned char condition_get_sev(const Condition* cond);
