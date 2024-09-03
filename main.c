#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "lib/include/shared.h"

#include "lib/include/adt/condition.h"
#include "lib/include/adt/xrmo.h"

#include "lib/include/ai/ai.h"

#include "lib/include/obj/patient.h"
#include "lib/include/obj/exam.h"
#include "lib/include/obj/report.h"

#include "lib/include/handlers/patientQueue.h"
#include "lib/include/handlers/xrmm.h"
#include "lib/include/handlers/examQueue.h"
#include "lib/include/handlers/medic.h"

#include "lib/include/db/db.h"

#ifdef _WIN32 || _WIN64
#define CLEAR_SCREEN "cls"

#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"

#endif

#define SIMULATION_TIMES_UNIT 43200
#define CONDITION_TRACKER "Cancer de Pulmao"

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


void add_patient(PatientQueue* pq, int p_id, int i)
{
    Patient* p;

    p = patient_create(p_id, "Generic Name", get_current_time());
    
    if(p == NULL)
    {
        perror("MEMORY ERROR");
        exit(0);
    }

    pq_insert(pq, p);
    db_insert_patient(pat, p, i); 
}


void add_exam(ExamQueue* eq, xrMachineOutput* xrmo, int e_id, int i)
{
    Exam* e;

    e = exam_create(e_id, xrmo_get_xrmid(xrmo), xrmo_get_pid(xrmo), cond_define(), get_current_time(), i);

    if(e == NULL)
    {
        perror("MEMORY ERROR");
        exit(0);
    }

    db_insert_exam(exa, e, i);
    eq_insert(eq, e);

    xrmo_free(xrmo);
}


Report* medic_report(Medic* m, const ID report_id)
{
    Report* r;
    Exam* e;
    Condition* c;

    if(m == NULL)
    {
        perror("ERROR");
        exit(1);
    }

    e = medic_get_exam(m);
    c = exam_get_cond(e);

    if(rand()%100 >= 80)
    {
        do
        {
            c = cond_define();
        } while (!strcmp(cond_get_name(c), cond_get_name(exam_get_cond(e))));
    }

    r = report_create(report_id, exam_get_id(e), True, c, exam_get_time(e));

    return r;
}


void simulation_relaotry(int id_p, int pq_size, int e_id, int r_id, int tml, int num_laudos, int tempo_laudo)
{
    printf("Pacientes que visitaram o hospital: %d\nPacientes na fila: %d\nExames ja realizados: %d\nPercentual com laudo: %.2f%%\nTempo medio de laudo: %.2f UT\nTempo medio de laudo por %s: %.2f\n", id_p, pq_size, e_id, ((double)r_id)/e_id * 100, ((double)tml) / r_id, CONDITION_TRACKER, ((double)tempo_laudo) / num_laudos);
}


int main() {
    /* Simulation Variable Declare */
    int simulation_count;
    ID patient_id;
    ID xrm_ids[] = {1, 2, 3, 4, 5};
    ID exam_id;
    ID reports_id;
    
    int exam_total_time;
    int tracker_report_total_time;
    int tracker_report_num;
    int exam_extra_time;

    PatientQueue* pq;
    XRMachineManager* xrmm;
    xrMachineOutput* xrmo;
    ExamQueue* eq;
    Medic* m;

    /* Simulation Variable Attribuition */
    patient_id = 0, exam_id = 0, reports_id = 0;
    exam_total_time = 0, tracker_report_total_time = 0, tracker_report_num = 0;

    pq = pq_create();
    xrmm = xrmm_create(5, xrm_ids);
    eq = eq_create(6);
    m = medic_create();


    /* Simulation Ambience Prepare */
    srand(time(NULL));
    db_create_folder();
    db_create_patient();
    db_create_exam();
    db_create_report();


    /* Open database */
    pat = fopen("output/db_patient.txt", "a+");
    exa = fopen("output/db_exam.txt", "a+");
    rep = fopen("output/db_report.txt", "a+");


    /* SIMULATION MAIN LOOP */
    for(simulation_count = 0; simulation_count < SIMULATION_TIMES_UNIT; simulation_count++)
    {
        if(simulation_count % 432 == 0)
        {
            simulation_relaotry(patient_id, pq_get_size(pq), exam_id, reports_id, exam_total_time, tracker_report_num, tracker_report_total_time);    
        }

        if(rand()%100 < 20)
        {
            patient_id++;
            add_patient(pq, patient_id, simulation_count);
        }

        if(xrmm_alloc_machine(xrmm, pq_get_fisrt_id(pq)))
            pq_remove_and_free(pq);   

        xrmo = xrmm_dealloc_machie(xrmm);
        if(xrmo != NULL)
        {
            exam_id++;
            add_exam(eq, xrmo, exam_id, simulation_count);
        }
        
        if(medic_check_isEmpty(m))
        {
            Exam* e = eq_remove(eq);
            int extra_time;

            if(e == NULL)
                continue;

            extra_time = simulation_count - exam_get_itime(e);

            medic_alloc(m, e);

            exam_total_time += extra_time; 

            if(!strcmp(cond_get_name(exam_get_cond(e)), CONDITION_TRACKER))
            {
                tracker_report_num++;
                tracker_report_total_time += extra_time;
            }
        }
        
        if(medic_dealloc(m))
        {
            Report* r;

            reports_id++;
            r = medic_report(m, reports_id);
            db_insert_report(rep, r, simulation_count);
            
            exam_free(medic_get_exam(m));

            report_free(r);
        } 
    }
   
    exam_extra_time = reports_id;

    simulation_relaotry(patient_id, pq_get_size(pq), exam_id, reports_id, exam_total_time, tracker_report_num, tracker_report_total_time);

    fclose(pat);

    /* SIMULATION EXTRA HOUR LOOP */
    while(pq_get_size(pq) || !xrmm_check_isEmpty(xrmm) || eq_get_size(eq) || !medic_check_isEmpty(m))
    {
        printf("%d - %d - %d - %d - %d\n", pq_get_size(pq), !xrmm_check_isEmpty(xrmm), eq_get_size(eq), medic_check_isEmpty(m), medic_get_itime(m));
        sleep(1);

        if(xrmm_alloc_machine(xrmm, pq_get_fisrt_id(pq)))
            pq_remove_and_free(pq);   

        xrmo = xrmm_dealloc_machie(xrmm);
        if(xrmo != NULL)
        {
            exam_id++;
            add_exam(eq, xrmo, exam_id, simulation_count);
        }
        
        if(medic_check_isEmpty(m))
        {
            Exam* e = eq_remove(eq);
            int extra_time;

            if(e == NULL)
                continue;

            extra_time = simulation_count - exam_get_itime(e);

            medic_alloc(m, e);

            exam_total_time += extra_time; 

            if(!strcmp(cond_get_name(exam_get_cond(e)), CONDITION_TRACKER))
            {
                tracker_report_num++;
                tracker_report_total_time += extra_time;
            }
        }
        
        if(medic_dealloc(m))
        {
            reports_id++;
            db_insert_report(rep, medic_report(m, reports_id), simulation_count);
        }    
    }
    
    printf("Extra Hour Reports: %d", reports_id-exam_extra_time);

    fclose(exa);
    fclose(rep);

    return 0;
}