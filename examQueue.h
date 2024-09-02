#pragma once

typedef struct report Report;
typedef struct examQueue ExamQueue;


struct report
{
    int id;
    int e_id;
    int f_ia;
    int time;
    Condition* cond;
    Report* next;
};


ExamQueue* eq_create(const int pn);
void eq_insert(ExamQueue* eq, Report* r);

Report* report_create(const int id, const int e_id, Condition* cond, const int time);
void report_free(Report* r);
Report* eq_remove(ExamQueue* eq);
int eq_get_size(const ExamQueue* eq);
