#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int wfd=open(argv[argc-1],O_WRONLY);
	if (argc < 2) 
	{
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        exit(1);
    }

	for(int i=1;i<argc-1;i++)
	{
		int n;
		char buf[50];
		int fd=open(argv[i],O_RDONLY);
		if(fd==-1)
		{
			printf("open error \n");
	        exit(1);
	    }
	    else{
			while((n=read(fd,buf,10))>0){
				if(write(wfd,buf,n)!=n){
					printf("write error\n");
					exit(1);
				}
			}
			if(n==-1){
				printf("read error\n");
				exit(1);
			}
			if (close(fd)==-1){
				printf("close error\n");
				exit(1);
			}
		}
	}
	return 0;
}
