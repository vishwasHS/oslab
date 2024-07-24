#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<semaphore.h>

typedef struct 
{
    int bal;
} shmpacket;

int main() 
{
    int shmid,damt,wamt,sleeptime,option,pid;
    shmpacket *ptr;
    sem_t mutex[2];
    shmid=shmget(200,sizeof(shmpacket),IPC_CREAT|0666);
    ptr=(shmpacket*)shmat(shmid,0,0);
    ptr->bal=5000;
    sem_init(&mutex[0],1,1); 
    sem_init(&mutex[1],1,1); 
    pid=fork();
    if (pid==0) 
    {
        
        do 
        {
            sem_wait(&mutex[1]); 
            printf("C: entering cs\n");
            printf("C: enter the amount to withdraw\n");
            wamt=rand()%100;
            printf("C: withdraw amt = %d\n",wamt);
            if(ptr->bal-wamt>=100) 
            {
                printf("C: withdraw amt = %d\n",wamt);
                ptr->bal=ptr->bal-wamt;
                printf("C: remaining balance = %d\n",ptr->bal);
            } 
            else 
            {
                printf("C: withdraw not possible - minimum balance problem\n");
                printf("C: current balance = %d\n",ptr->bal);
            }
            sem_post(&mutex[1]); 
            sleeptime=rand()%5;
            sleep(sleeptime);
            option=rand()%10;
        } 
        while(option!=0);
        exit(0);
    }

    if(pid>0) 
    {
     
        do 
        {
            sem_wait(&mutex[0]); 
            printf("P: entering cs\n");
            printf("P: enter the amount to deposit\n");
            damt = rand() % 1000;
            printf("P: deposit amt = %d\n",damt);
            ptr->bal=ptr->bal+damt;
            printf("P: balance = %d\n",ptr->bal);
            sem_post(&mutex[0]); 
            sleeptime = rand() % 5;
            sleep(sleeptime);
            option=rand()%10;
        } 
        while(option!=0);
        exit(0);
    }
    sem_destroy(&mutex[0]);
    sem_destroy(&mutex[1]);
    return 0;
}
