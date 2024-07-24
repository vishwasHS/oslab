#include<stdio.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<math.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>

void sigfn1(int signo)
{
	printf("parent work is over,child-you can proced\n");
}
void sigfn2(int signo)
{
	printf("child work is over,parent -you can proced\n");
}

int main()
{
	signal(SIGUSR1,sigfn1);
	signal(SIGUSR2,sigfn1);
	int temp;
	key_t key=ftok("twob",165);
	int shmid=shmget(key,10*sizeof(int),IPC_CREAT|0666);
	if(shmid>0)
	{
		printf("it is okshm id=%d\n",shmid);
        int *ptr=(int*)(shmat(shmid,0,0));
        int pid=fork();
        if(pid==0)
        {
			printf("child:child is going to wait for data\n");
			pause();
			printf("child:got signal from parent\n");
			for(int i=0;i<10;i++)
			{
				printf("child:%d\n",*(ptr+i));
			}
			printf("child:im going to sort\n");
			for(int i=0;i<9;i++)
			for(int j=i+1;j<10;++j)
			if(*(ptr+i)>*(ptr+j))
			{
				temp=*(ptr+i);
				*(ptr+i)=*(ptr+j);
				*(ptr+j)=temp;
			}
			printf("child:sorted data\n");
			for(int i=0;i<10;i++)
			{
				printf("child:%d\n",*(ptr+i));
			}
			printf("child: I am signalling parent \n");
			kill(getpid(),SIGUSR2);
			printf("child:iam going to terminate\n");
		}
		else
		{
			printf("parent is writting data \n");
			printf("parent:enter 10 data\n");
			for(int i=0;i<10;i++)
			{
				scanf("%d",ptr+i);
			}
			printf("parent:data written in memory:\n");
			for(int i=0;i<10;i++)
			{
				printf("parent:%d\n",*(ptr+i));
			}
                printf("parent is going to signal\n");
				kill(pid,SIGUSR1);
				printf("parent is going to wait for child signal\n");
				pause();
				printf("P:parent got signal\n");
				printf("P:sorted data\n");
				for(int i=0;i<10;i++)
				{
					printf("parent=%d\n",*(ptr+i));
				}
			
         }
      }
}
      

