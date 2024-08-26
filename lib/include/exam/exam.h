#pragma once

enum EXAM_FREE_CODE {DESTROY, DESTROY_AND_GET_NEXT, ALLOCATE_CONDITION_ERROR, ALLOCATE_TIMESTAMP_ERROR};

Exam* exam_free(Exam* e, unsigned char free_code);

Exam* exam_create(const unsigned int id, const unsigned int xr_id, const unsigned int p_id, const Condition* cond, const TM* timestamp);

unsigned int exam_get_id(const Exam* exam);

unsigned int exam_get_xrid(const Exam* exam);

unsigned int exam_get_pid(const Exam* exam);

Condition* exam_get_condition_ptr(const Exam* exam);

TM* exam_get_tm_ptr(const Exam* exam);

Exam* exam_get_next_ptr(const Exam* exam);

void exam_set_next(Exam* dest, Exam* src);

int exam_sizeof();