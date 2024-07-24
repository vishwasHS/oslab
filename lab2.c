#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int x=8;
int main()
{
	int y=10,pid;
	printf("I am parent process before child and my pid =%d\n",getpid());
	pid=fork();
	if(pid==0)
	{
		int z=100;
		sleep(10);
		printf("child z=%d\n",z);
		printf("y=%d child has x =%d\n",y,++x);
		printf("I am child proces my pid =%d,my parent id=%d \n",getpid(),getppid());
	}
	else
	{
		int z=2000;
		sleep(20);
		printf("parent z is =%d \n",z);
		printf("I am parent process after child and my pid =%d,and my child pid is =%d \n",getpid(),pid);
		_exit(1);
	}
	return 0;
}
