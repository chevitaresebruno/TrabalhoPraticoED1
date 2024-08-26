#pragma once

void examqueue_free(ExamQueue* exam_queue);

ExamQueue* examqueue_create();

void examqueue_insert(ExamQueue* exam_queue, Exam* exam);

Exam* examqueue_remove(ExamQueue* eq);
