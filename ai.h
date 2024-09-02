#pragma once

/*

*/
typedef struct condition Condition;

struct condition
{
    char* name;
    int sev;
};

/*

*/
Condition* cond_create(const char* name, const int sev);

/*

*/
Condition* cond_define();

/*

*/
void cond_free(Condition* cond);