#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int x=8;
int main()
{
	int y=10;
	if (fork()==0)
	printf("y=%d child has x =%d \n",y,++x);
	else
	printf("parent has x =%d y=%d \n",--x,y);
	return 0;
}
