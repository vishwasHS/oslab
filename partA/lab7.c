#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd,n;
	char buf[11];
	fd=open("lab4.c",O_RDONLY);
    if (fd==-1)
    {
	   printf("open error \n");
	   exit(1);
     }
    else{
	    while((n=read(fd,buf,10))>0)
	    {
		   printf("%s",buf);
		   write(1,buf,n);
	    }
       }
}
