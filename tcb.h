/**
 * CSE 330 Assignment 2
 * Travis Delly
 * 1210230252
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>


typedef struct Queue {
    struct TCB_t *head;
} Queue;

typedef struct TCB_t {
    struct TCB_t *prev;
    struct TCB_t *next;
    ucontext_t context;
    int payload;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size){

    int threadID = tcb->payload;

    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse

    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    
    tcb->payload = threadID;
    makecontext(&tcb->context, function, 0);// context is now cooked
}