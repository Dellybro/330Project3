/**
 * CSE 330 Assignment 2
 * Travis Delly
 * 1210230252
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

typedef struct Queue {
    struct TCB_t *head;
} Queue;

struct Queue *RunQ;

struct Queue * InitQueue() {
    return malloc(sizeof(Queue));
}

struct TCB_t *newTCB(int threadId){
    struct TCB_t* node = (struct TCB_t*)malloc (sizeof (struct TCB_t));
    node->payload = threadId;
    node->prev = NULL;
    node->next = NULL;

    totalQueues++;
    
    return node;
}

void AddQueue(Queue * queue, TCB_t * element)
{
    if(queue->head == NULL) {
        queue->head = element;
        queue->head->prev = queue->head;
        queue->head->next = queue->head;
    } else {
        TCB_t * tail = queue->head->prev;
        tail->next = element;
        element->prev = tail;
        tail = tail->next;


        tail->next = queue->head;
        queue->head->prev = tail;
    }
}

struct TCB_t * DelQueue(Queue * queue)
{
    // No elements
    if(queue->head == NULL){
        return NULL;
    } else if (queue->head->next == queue->head) {
        TCB_t * temp = queue->head;
        queue->head = NULL;
        return temp;
    } else {
        TCB_t * temp = queue->head;
        TCB_t * tail = queue->head->prev;

        if(queue->head->next == queue->head){
            queue->head = NULL;
        }else {
            queue->head = queue->head->next;
            queue->head->prev = tail;
            tail->next = queue->head;
        }
        return temp;
    }
}

void RotateQ(Queue * queue){
    queue->head = queue->head->next;
}