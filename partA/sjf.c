#include<stdlib.h>
#include<stdio.h>
typedef struct process
{
	int pid;
	int at,cbt,tat,wt,st,ct;
}process;
int main()
{
	process p[20],t;
	int i,j,k,n,c=0;
	float sumtat=0,sumwt=0,avgtat=0,avgtwt=0;
	printf("enter number of processes\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		p[i].tat=0;
		p[i].wt=0;
		p[i].ct=0;
	}
	for (i=0;i<n;i++)
	{
		printf("enter process id,arrival time,cpu burst time of process %d\n",i+1);
		scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].cbt);
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n;j++)
		{
			if(p[j].at>p[j+1].at)
			{
				t=p[j];
			    p[j]=p[j+1];
			    p[j+1]=t;
			}
		}
	}
	for(i=1;i<n;i++)
	{
		for(k=1;k<n-1;k++)
		{
			for(j=1;j<n-k-1;j++)
			{
				if(p[j].cbt>p[j+1].cbt)
			    {
					 if(p[j+1].at<c)
					 {
						 t=p[j];
				         p[j]=p[j+1];
				         p[j+1]=t;
				     }
				}
			}
		}
	}
	if(c<=p[i].at)
	{
		p[i].st=p[i].at;
	}
	else
	{
		p[i].st=c;
		p[i].ct=p[i].st+p[i].cbt;
		c=p[i].ct;
		p[i].tat=p[i].ct-p[i].at;
		sumtat=p[i].tat;
		p[i].wt=p[i].st-p[i].at;
		sumwt=p[i].wt;
	}
		
	avgtat=sumtat/n; 
	avgtwt=sumwt/n;
	printf("pid \t At \t CPU BT\t TAT\t WT\t ST\t CT\t");
	for(i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t",p[i].pid,p[i].at,p[i].cbt,p[i].tat,p[i].wt,p[i].st,p[i].cbt);
	}
	printf("average TAT %f \n",avgtat);
	printf("average WT %f \n",avgtwt);
	return 0;
}
	
	
