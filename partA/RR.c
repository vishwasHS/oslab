#include<stdlib.h>
#include<stdio.h>
typedef struct process {
    int pid;
    int at, cbt, tat, wt, st, ct;
} process;

int main()
 {
    process p[20];
    int n, tq, r[20];
    float sumtat=0,sumwt=0,avgtat=0,avgtwt=0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) 
    {
        printf("Enter process id, arrival time, and CPU burst time of process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].cbt);
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].ct = 0;
        r[i] = p[i].cbt;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    int time = 0;
    int complete = 0;

    while (complete < n) 
    {
        for (int i=0;i<n;i++) 
        {
            if (r[i]>0) 
            {
                if (r[i]>tq) 
                {
                    time+=tq;
                    r[i]-=tq;
                } 
                else 
                {
                    time += r[i];
                    p[i].ct=time;
                    r[i] = 0;
                    complete++;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].cbt;
                    sumtat += p[i].tat;
                    sumwt += p[i].wt;
                }
            }
        }
    }

    avgtat = sumtat/n;
    avgtwt = sumwt/n;

    printf("\nPID\tAT\tCBT\tTAT\tWT\tCT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].cbt,p[i].tat,p[i].wt,p[i].ct);
    }
    printf("Average TAT: %.2f\n", avgtat);
    printf("Average WT: %.2f\n", avgtwt);

    return 0;
}
