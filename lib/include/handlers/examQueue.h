#pragma once

/*
    Feature:
        ExamQueue is a struct that represents a queue of exams operating in a FIFO (First In, First Out) manner.
    
    Attributes:
        QueueSize size -> Acutal number of elements in queue;
        int pn -> Number of priority exists (example, by defult in simulation lung cancer has priority 6, an it is max priority, so the pn attribut must be 6);
        Exam* first -> A pointer to first element in queue; and
        Exam** last_per_p -> A pointer to last element in queue by priority (for example, if the queue has 2 exam inside, on of severity 2 end other severity 4, the last_per_p[4] contains the exam with severity 4).
    
    Verbs:
        Create -> Creates a new ExamQueue;
        Get -> Retrieves an attribute from the ExamQueue structure;
        Insert -> Inserts a Exam into the queue; and
        Remove -> Removes a Exam from the queue.
*/
typedef struct examQueue ExamQueue;


/*
    Verb: Create

    Args:
        const int priority_number: The max number of priority you want.

    Return:
        A pointer to a newly created ExamQueue. If memory allocation fails, returns NULL.
*/
ExamQueue* eq_create(const int priority_number);


/*
    Verb: Get

    Args:
        ExamQueue* examQueue -> Pointer to the ExamQueue object from which data is retrieved.
    
    Return:
        The size of Queue. If argument is NULL or queue is empty, the function may return -1.
*/
QueueSize eq_get_size(const ExamQueue* examQueue);


/*
    Verb: Insert
    
    Args:
        ExamQueue* examQueue -> Pointer to the ExamQueue where data will be inserted; and
        Exam* exam -> Pointer to the Exam to be inserted into the queue.
*/
void eq_insert(ExamQueue* examQueue, Exam* exam);


/*
    Verb: Remove
    
    Args:
        ExamQueue* examQueue -> Pointer to the ExamQueue from which a Exam will be removed.
    
    Return:
        A pointer to the removed Exam. Returns NULL if the queue is empty.
*/
Exam* eq_remove(ExamQueue* examQueueq);

