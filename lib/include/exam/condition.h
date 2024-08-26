#pragma once


int condition_how_much();


void condition_copy(Condition* dest, const Condition* src);


double condition_get_prob(const Condition* condition);

void cJSON_Parse_Condition(const cJSON* json, Condition* condition);


char* condition_get_name(const Condition* condition);

unsigned char condition_get_sev(const Condition* cond);
