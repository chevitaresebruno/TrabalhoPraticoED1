#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "exam.h"


Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time) {
    Exam *new_exam = (Exam*)malloc(sizeof(Exam));
    
    /*Memory check for exam*/
    if (new_exam == NULL) {
        perror("Failed to allocate memory for new exam");
        exit(EXIT_FAILURE);
    }
    new_exam->id = id;
    new_exam->patient_id = patient_id;
    new_exam->rx_id = rx_id;
    new_exam->time = (struct tm*)malloc(sizeof(struct tm)); /* Aloca memória para um novo ponteiro para manter o escopo (a variável referente ao parâmetro time não será alterada caso o new_exam->time seja alterado)*/

    /*Memory Check for time*/
    if (new_exam->time == NULL) {
        perror("Failed to allocate memory for exam time");
        free(new_exam);
        exit(EXIT_FAILURE);
    }
    *(new_exam->time) = *time;
    return new_exam;
}

void destroy_exam(Exam *exam) {
    if (exam != NULL) {
        free(exam->time);
        free(exam);
    }
}

int get_exam_id(Exam *exam) {
    if (exam != NULL) {
        return exam->id;
    }
    return NULL; 
}

int get_exam_patient_id(Exam *exam) {
    if (exam != NULL) {
        return exam->patient_id;
    }
    return NULL;
}

int get_exam_rx_id(Exam *exam) {
    if (exam != NULL) {
        return exam->rx_id;
    }
    return NULL; 
}


struct tm* get_exam_time(Exam *exam) {
    if (exam != NULL) {
        return exam->time;
    }
    return NULL;
}


void print_exam(Exam *exam) {
    if (exam != NULL) {
        printf("Exam ID: %d\n", exam->id);
        printf("Patient ID: %d\n", exam->patient_id);
        printf("RX ID: %d\n", exam->rx_id);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", exam->time);
        printf("Time: %s\n", buffer);
    }
}