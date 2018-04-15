/**
 * CSE 330 Assignment 2
 * Travis Delly
 * 1210230252
 * 
*/

#include "threads.h"

typedef struct Semaphore {
    int value;
} Semaphore;

void InitSem(Semaphore *sem, int value){
    sem = malloc(sizeof(Semaphore));
    sem->value = value;
}

void P(Semaphore *sem) {

    if ( sem->value > 0){
        sem->value--;
    } else {
        

		struct TCB_t *current = DelQueue(RunQ);
		AddQueue(RunQ, current);
		swapcontext(&current->context, &RunQ->head->context);

        /* Thread finishes */

        P(sem);  
    }
}

void V(Semaphore *sem){
    sem->value++;


    if (sem->value <= 0) {	
		RotateQ(RunQ);
	}

	yield();
}