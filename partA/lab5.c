#include<stdio.h>
 
int main()
{
	int i,temp[30],at[30],bt[30],tat[30],wt[30],n;
	float atat=0,awt=0;
	printf("enter number of processes\n");
	scanf("%d",&n);
	printf("enter arrival time");
	for(i=0;i<n;i++)
	{
		scanf("%d",&at[i]);
	}
	printf("enter burst time");
	for(i=0;i<n;i++)
	{
		scanf("%d",&bt[i]);
	}
	temp[0]=0;
	printf("prs\t at\t bt\t tat\t wt\n");
	for(i=0;i<n;i++)
	{
		wt[i]=0;
		tat[i]=0;
		temp[i+1]=temp[i]+bt[i];
		wt[i]=temp[i]-at[i];
		tat[i]=wt[i]+bt[i];
		awt=awt+wt[i];
		atat=atat+tat[i];
		printf("%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],tat[i],wt[i]);
	}
	awt=awt/n;
	atat=atat/n;
	printf("avg waiting time=%f",awt);
	printf("avg turn around time=%f",atat);
}

			
