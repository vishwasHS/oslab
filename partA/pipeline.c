#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int fd[2];
	pid_t pid;
	if(pipe(fd)==-1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid=fork();
	if(pid<0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
    if(pid==0)
    {
		int n;
	    int *numbers;
	    close(fd[0]);
	    close(fd[1]);
	    read(fd[0],&n,sizeof(n));
	    numbers=(int*)malloc(n*sizeof(int));
	    read(fd[0],&numbers,n*sizeof(int));
		write(fd[1],numbers,n*sizeof(int));
		close(fd[1]);
		free(num);
		exit(EXIT_SUCCESS);
	}
	else
	{
       
        int n;
        printf("enter n numbers");
        scanf("%d",&n);
        int *numbers=(int*)malloc(n+1*sizeof(int));
		close(fd[1]);
		numbers[0]=n;
		for(int i=0;i<n;i++)
		{
			scanf("%d",numbers[i])
		}
		read(fd[0],&numbers,sizeof(numbers));
		close(fd[0]);
		
		
	}
	return 0;
} 
   
