#ifndef PATIENT_H
#define PATIENT_H


/*
    Struct responsável por modelar um exame.
*/
typedef struct patient {
    int id;
    char* name;
    struct tm* birthdate;
} Patient;


/*
    TODAS as funções abaixo que não retornam o tipo void verificam se os valores passados não estão nulos e caso estejam retornam nulo.
*/

/*
    Aloca memória dinamicamente e retorna um ponteiro para o paciente criado.
    Caso não tenha memória suficiente para alocar a estrutura patient e a estrutura birthdate alerta um erro e finaliza o código.
*/
Patient* create_patient(int id, char* name, struct tm* birthdate);


int get_patient_id(Patient* p);

const char* get_patient_name(Patient* p);

struct tm* get_patient_birthdate(Patient* p);

/*
    Desaloca memória dos ponteioros e libera a memória da estrutura
*/
void destroy_patient(Patient* p);

#endif