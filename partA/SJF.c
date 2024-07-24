#include<stdlib.h>
#include<stdio.h>
typedef struct process
{
	int pid;
	int at,cbt,tat,wt,st,ct;
}process;
int main()
{
	process p[20];
	int i,n;
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
	int complete=0,time=0,mbt,mbtin;
	while(complete<n)
	{
		mbt=1000000;
		mbtin=-1;
		for(i=0;i<n;i++)
		{
			if(p[i].at<=time&&p[i].ct==0&&p[i].cbt<mbt)
			{
				mbt=p[i].cbt;
				mbtin=i;
			}
		}
		if(mbtin==-1)
		{
			time++;
			continue;
		}
		p[mbtin].st=time;
		p[mbtin].ct=p[mbtin].st+p[mbtin].cbt;
		p[mbtin].tat=p[mbtin].ct-p[mbtin].at;
		p[mbtin].wt=p[mbtin].tat-p[mbtin].cbt;
		sumtat+=p[mbtin].tat;
		sumwt+=p[mbtin].wt;
		time=p[mbtin].ct;
		complete++;
	}
	avgtat=sumtat/n; 
	avgtwt=sumwt/n;
	printf("pid \t At \t CPU BT\t TAT\t WT\t ST\t CT\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].cbt,p[i].tat,p[i].wt,p[i].st,p[i].cbt);
	}
	printf("average TAT %f \n",avgtat);
	printf("average WT %f \n",avgtwt);
	return 0;
}
		
		
	
