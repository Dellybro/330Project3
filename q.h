/**
 * CSE 330 Assignment 2
 * Travis Delly
 * 1210230252
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

int totalQueues;

void printQ(struct Queue *list){
    struct TCB_t *current = list->head;
    /* Make sure current isn't null */
    if(current == NULL){
        return;
    }else if(current->next == NULL){
        /* if no next, only print current payload */
        printf("Current: %i \n", current->payload);
    } else {
        /* Loop until current next is head while printing */
        while(current->next != list->head){
            printf("Current: %i \n", current->payload);
            current = current->next;
        }
        printf("Current: %i \n", current->payload);
    }
}


struct TCB_t *newTCB(int threadId){
    struct TCB_t* node = (struct TCB_t*)malloc (sizeof (struct TCB_t));
    node->payload = threadId;
    node->prev = NULL;
    node->next = NULL;

    totalQueues++;
    
    return node;
}

/* Sets up the queue? */
void initQueue(struct Queue *list){
    list = (struct Queue*)malloc (sizeof (struct Queue));
    list->head = NULL;
}

/* Deletes head of queue */
struct TCB_t *DelQueue(struct Queue *list){
    if(list->head == NULL){
        return NULL;
    }


    struct TCB_t* previousHead = list->head;
    if(previousHead->next == NULL){
        list->head = NULL;
        return previousHead;
    }

    struct TCB_t* tail = previousHead->prev;
    struct TCB_t* newHead = previousHead->next;
    
    //Make head = to head->next
    //make new head prev = to previousHead previous
    //Make the last node next = to new list head
    tail->next = newHead;
    newHead->prev = tail;
    list->head = newHead;


    previousHead->next = NULL;
    previousHead->prev = NULL;

    return previousHead;
}

/* Adds to tail. */
void AddQueue(Queue *list, TCB_t *newItem){

    if(list->head == NULL){
        list->head = newItem;
        return;
    } else {

        struct TCB_t *current = list->head;

        if(current->next == NULL){
            current->next = newItem;
            current->prev = newItem;
            newItem->next = current;
            newItem->prev = current;
        } else {

            while(current->next != list->head){
                current = current->next;
            }

            current->next = newItem;
            newItem->prev = current;
            newItem->next = list->head;
            list->head->prev = newItem;
        }
    }
    
}


/* counter clock wise, 123 becomes 231, use delqueue to pop off 1 and than put it at tail of queue */
void RotateQ(struct Queue *list){
    struct TCB_t *deleted = DelQueue(list);
    if(deleted){
        AddQueue(list, deleted);
    }
}
