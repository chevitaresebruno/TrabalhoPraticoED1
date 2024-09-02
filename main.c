#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "patient.h"
#include "xr.h"
#include "ai.h"
#include "examQueue.h"
#include "medicManager.h"
#include "db.h"


#define SIMULATION_TIMES_UNIT 43200
#define CONDITION_TRACKER "Fibrose Pulmonar"

FILE* pat;
FILE* exa;
FILE* rep;


struct tm* get_current_time() {
    time_t t;
    struct tm* tw;

    time(&t);
    tw = localtime(&t);

    return tw;
}


void add_patient(PatientQueue* pq, int* p_id, int i)
{
    Patient* p;

    (*p_id)++;
    p = patient_create(*p_id, "Generic Name", get_current_time());
    
    pq_insert(pq, p);
    db_insert_patient(pat, p, i); 
}


void add_exam(ExamQueue* eq, xrMachineOutput* xrmo, int* e_id, int i)
{
    Condition* cond;

    (*e_id)++;
    cond = cond_define();

    db_insert_exam(exa, *e_id, xrmo->xrm_id, xrmo->p_id, cond->name, get_current_time(), i);

    eq_insert(eq, report_create(*e_id, *e_id, cond, i));

    free(xrmo);
}


void simulation_relaotry(int id_p, int pq_size, int e_id, int r_id, int tml, int num_laudos, int tempo_laudo)
{
    system("clear");
    printf("Pacientes que visitaram o hospital: %d\nPacientes na fila: %d\nExames ja realizados: %d\nPercentual com laudo: %.2f%%\nTempo medio de laudo: %.2f UT\nTempo médio de laudo por %s: %.2f UT\n", id_p, pq_size, e_id, ((double)r_id)/e_id * 100, ((double)tml) / r_id, CONDITION_TRACKER, ((double)tempo_laudo) / num_laudos);

    sleep(2);
}


int main() {
    int i;
    int extra = 0;
    int patient_id;
    int xrm_ids[] = {1, 2, 3, 4, 5};
    int exam_id;
    int rep_id;
    int tempo_medio_exam;

    int tempo_meio_laudo = 0, num_de_laudos = 0;

    PatientQueue* pq;
    xrMachineManager* xrmm;
    xrMachineOutput* xrmo;
    ExamQueue* eq;
    Medic* m;

    patient_id = 0;
    exam_id = 0;
    rep_id = 0;
    tempo_medio_exam = 0;
    pq = pq_create();
    xrmm = xrmm_create(sizeof(xrm_ids), xrm_ids);
    eq = eq_create(6);
    m = medic_create();


    srand(time(NULL));
    db_create_patient();
    db_create_exam();
    db_create_report();


    pat = fopen("db_patient.txt", "a+");
    exa = fopen("db_exam.txt", "a+");
    rep = fopen("db_report.txt", "a+");


    for(i = 0; i < SIMULATION_TIMES_UNIT; i++)
    {
        if(rand()%100 < 20)
            add_patient(pq, &patient_id, i);

        if(xrmm_alloc_m(xrmm, pq_get_fisrt_id(pq)))
            pq_remove_and_free(pq);   

        xrmo = xrmm_dealloc_m(xrmm);
        if(xrmo != NULL)
            add_exam(eq, xrmo, &exam_id, i);
        
        
        if(medic_alloc(m, eq))
        {
            tempo_medio_exam += (i - medic_get_report(m)->time);
            
            if(strcmp(medic_get_report(m)->cond->name, CONDITION_TRACKER) == 0)
            {
                num_de_laudos++;
                tempo_meio_laudo += (i - medic_get_report(m)->time);
            }
            
            rep_id++;
        }
        
        if(medic_dealloc(m))
        {
            db_insert_report(rep, medic_report(m), rep_id, get_current_time(), i);
        }
        
        if(i % 4320 == 0)
            simulation_relaotry(patient_id, pq_get_size(pq), exam_id, rep_id, tempo_medio_exam, num_de_laudos, tempo_meio_laudo);
    }
    
    
    simulation_relaotry(patient_id, pq_get_size(pq), exam_id, rep_id, tempo_medio_exam, num_de_laudos, tempo_meio_laudo);

    while(pq_get_size(pq) || !xrmm_is_empty(xrmm) || eq_get_size(eq) || medic_get_time(m))
    {
        if(xrmm_alloc_m(xrmm, pq_get_fisrt_id(pq)))
            pq_remove_and_free(pq);   

        xrmo = xrmm_dealloc_m(xrmm);
        if(xrmo != NULL)
            add_exam(eq, xrmo, &exam_id, i);
        
        if(medic_alloc(m, eq))
            {
                tempo_medio_exam += (i - medic_get_report(m)->time);
                if(strcmp(medic_get_report(m)->cond->name, CONDITION_TRACKER) == 0)
                {
                    num_de_laudos++;
                    tempo_meio_laudo += (i - medic_get_report(m)->time);
                }
            }

        if(medic_dealloc(m))
        {
            rep_id++;
            extra ++;
            db_insert_report(rep, medic_report(m), rep_id, get_current_time(), i);
        }
        i++;
    }   

    printf("Laudos realizados em hora extra: %d \n", extra);

    fclose(pat);
    fclose(exa);
    fclose(rep);

    return 0;
}