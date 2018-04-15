/**
 * CSE 330 Assignment 1 Threading using TCB's
 * Travis Delly
 * 1210230252
 * 
*/

#include <unistd.h>
#include "sem.h"

Semaphore  *R_sem, *W_sem, *mutex;
int rc = 0, wc = 0, rwc = 0, wwc = 0;

void reader(){
    
    while( 1 > 0 ){

        P(mutex);
        if(wwc > 0 || wc > 0){
            rwc++;
            V(mutex);
            P(R_sem);
            P(mutex);
            rwc--;
        }

        rc++;
        V(mutex);

        /* Read */
        sleep(1);
        printf("Reader read\n");

        P(mutex);
        rc--;
        if(rc == 0 && wwc > 0){
            V(W_sem);
        }
        V(mutex);
    }
}

void writer(){

    while( 1 > 0){

        P(mutex);
        if(rc > 0 || wc > 0){
            wwc++;
            V(mutex);
            P(W_sem);
            P(mutex);
            wwc--;
        }
        wc++;

        V(mutex);

        /* Write */
        sleep(1);
        printf("Writer wrote\n");

        P(mutex);
        wc--;
        if(rwc > 0){
            int i = 0;
            while(i < rwc){
                V(R_sem); //Loop through readers and allows them to read
                i++;
            }
        } else if(wwc > 0){
            V(W_sem);
        }

        V(mutex);

    }
    
}


int main(){
    printf("Started Program\n");

    RunQ = InitQueue();

	R_sem = InitSem(0);
	W_sem = InitSem(0);
    mutex = InitSem(1);

    start_thread(writer,1);
    start_thread(writer,2);
    start_thread(reader,3);
    start_thread(reader,4);
    start_thread(reader,5);

    run();

    return 1;
}