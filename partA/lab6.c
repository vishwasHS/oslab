#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main()
{
	key_t key=ftok("consumer.c",165);
	int shmid=shmget(key,10*sizeof(int),IPC_CREAT|0666);
	if(shmid>0)
	printf("it is okshm id=%d\n",shmid);
	int *ptr=(int*)(shmat(shmid,0,0));
	printf("write Data:");
	for(int i=0;i<10;i++)
	scanf("%d",ptr+i);
	
	printf("data written in memory initially :\n");
	for(int i=0;i<10;i++)
    printf("%d\n",*(ptr+i));
    
    int pid=fork();
    if(pid==0)
    {
		printf("child:data read from shared memory:\n");
		for(int i=0;i<10;i++)
		printf("child:%d\n",*(ptr+i));
		printf("child:I am going to update \n");
		for(int i=0;i<10;i++)
		{
			*(ptr+i)+=i;
			printf("child=%d\n",*(ptr+i));
		}
		sleep(60);
		printf("child:I am going to display updated copy by parent \n");
		for(int i=0;i<10;i++)
        printf("child:%d\n",*(ptr+i));
     }
     else
     {
		 sleep(10);
		 printf("p:I am reading shared memory \n");
		 for(int i=0;i<10;i++)
         printf("paarent :%d\n",*(ptr+i));
         sleep(10);
         printf("parent:I am going to update \n");
         for(int i=0;i<10;i++)
         {
			 *(ptr+i)+=20;
			 printf("parent :%d\n",*(ptr+i));
	     }
	     sleep(5);
	  }
	  shmdt(ptr);
	  return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
