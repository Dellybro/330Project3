/**
 * CSE 330 Assignment 2
 * Travis Delly
 * 1210230252
 * 
*/

#include "threads.h"

typedef struct Semaphore
{
    int value;
    Queue * tcb_queue;
} Semaphore;

Semaphore * InitSem(int value);

void P(Semaphore * sem);
void V(Semaphore * sem);

Semaphore * InitSem(int value)
{
    Semaphore * sem = ALLOC(Semaphore);
    sem->value = value;
    sem->tcb_queue = InitQueue();
    return sem;
}

// Take resource
void P(Semaphore * sem)
{
    sem->value--;
    if(sem->value < 0)
    {
        //printf("\nBlocked\n");
        TCB_t * tcb = DelQueue(RunQ);
        AddQueue(sem->tcb_queue, tcb);
        swapcontext(&tcb->context, &RunQ->head->context);
    }
}

// Release resource
void V(Semaphore * sem)
{
    sem->value++;
    if (sem->value <= 0)
    {
        //printf("\nAdded to RunQ\n");
        TCB_t * tcb = DelQueue(sem->tcb_queue);
        AddQueue(RunQ, tcb);
    }
    yield();
}