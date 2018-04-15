/**
 * CSE 330 Assignment 2
 * Travis Delly
 * 1210230252
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "q.h"

struct Queue *RunQ;
int global = 0;

void start_thread(void (*function)(void), int threadId){
//  begin pseudo code
//      allocate a stack (via malloc) of a certain size (choose 8192)
//      allocate a TCB (via malloc)
//      call init_TCB with appropriate arguments
//      call addQ to add this TCB into the “RunQ” which is a global header pointer
//  end pseudo code

    void *stack = malloc(8192);
    struct TCB_t* item = newTCB(threadId);
    init_TCB(item, function,stack, 8192);
    AddQueue(RunQ,item);
}


void run(){
    ucontext_t parent; // get a place to store the main context, for faking
    getcontext(&parent); // This gets the context that is currently running
    swapcontext(&parent, &(RunQ->head->context)); // start the first thread
}

void yield(){
    ucontext_t previousContext;
    getcontext(&previousContext);
    RunQ->head->context = previousContext;
    RotateQ(RunQ);
    swapcontext(&previousContext, &(RunQ->head->context));
}
