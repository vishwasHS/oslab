#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
typedef struct
{
	int PID,AT,BT,CT,ST,TAT,WT;
}process;
int main()
{
	int n,i,j,lc=0;
	float twt=0,tat=0,avg1,avg2;
	process p[20];
	printf("enter the no of process :\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("enter the PID,arrival time and brust time of process %d:\n",(i+1));
		scanf("%d%d%d",&p[i].PID,&p[i].AT,&p[i].BT);
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(p[j].AT>p[j+1].AT)
			{
				int t=p[j+1]; 
				p[j+1]=p[j];
				p[j]=t;
			}
		}
	}
	p[0].WT=0;
	for(i=0;i<n;i++)
	{
		if(lc<=p[i].AT)
		{
			p[i].ST=p[i].AT;
		}
		else
		{
			p[i].ST=lc;
			p[i].CT=p[i].ST+p[i].BT;
			lc=p[i].CT;
			p[i].TAT=p[i].CT-p[i].AT;
			p[i].WT=p[i].TAT-p[i].BT;
		}
	}
	printf("process id, arrival time ,brust time,complition time,turn around time,waitng time \n");
	for(i=0;i<n;i++)
	{
		printf("%d\t\t",p[i].PID);
		printf("%d\t\t",p[i].AT);
		printf("%d\t\t",p[i].BT);
		printf("%d\t\t",p[i].ST);
		printf("%d\t\t",p[i].CT);
		printf("%d\t\t",p[i].TAT);
		printf("%d\t\t",p[i].WT);
		tat+=p[i].TAT;
		twt+=p[i].WT;
	}
	avg1=(float)tat/n;
	avg2=(float)twt/n;
	printf("\n average turn around time=%f\n",avg1);
	printf("avarage waiting time =%f \n",avg2);
	return 0;
}
		
