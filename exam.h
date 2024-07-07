#ifndef EXAM_H
#define EXAM_H


/*
    Struct responsável por modelar um exame.
*/
typedef struct exam {
    int id;
    int patient_id;
    int rx_id;
    struct tm *time;
} Exam;


/*
    TODAS as funções abaixo que não retornam o tipo void verificam se os valores passados não estão nulos e caso estejam retornam nulo.
*/


/*
    Aloca memória dinamicamente e retorna um ponteiro para o exame criado.
    Caso não tenha memória suficiente para alocar a estrutra exam ou a estrutura tm* alerta um erro e finaliza o código.
*/
Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time);


/*
    Desaloca memória dos ponteioros e libera a memória da estrutura
*/
void destroy_exam(Exam *exam);

int get_exam_id(Exam *exam);

int get_exam_patient_id(Exam *exam);

int get_exam_rx_id(Exam *exam);

struct tm* get_exam_time(Exam *exam);

void print_exam(Exam *exam);


#endif