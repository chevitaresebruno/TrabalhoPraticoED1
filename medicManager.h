#pragma once

typedef struct medic Medic;

Medic* medic_create();
int medic_alloc(Medic* m, ExamQueue* eq);
int medic_dealloc(Medic* c);
Report* medic_report(Medic* m);
Report* medic_get_report(const Medic* m);

int medic_get_time(Medic* m);
