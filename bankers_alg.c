#include<stdio.h>
#include<stdbool.h>

int main()
{
    int n, m, i, j;
    int alloc[20][20], max[20][20], avail[20];
    
    printf("Enter the number of processes and resources:\n");
    scanf("%d %d", &n, &m);
    
    printf("Enter the matrix of maximum allocation:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter the matrix of current allocation:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter the available resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    
    

    // Safety algorithm to check for safe sequence
    bool finish[20] = {0};
    int safeSeq[20];
    int work[20];
    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }
    
    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                
                if (possible) {
                    for (j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        if (!found) {int need[20][20];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    
    // Print need matrix
    printf("Need Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
        printf("\n");
    }
            printf("System is not in safe state.\n");
            return 0;
        
    }
    
    printf("System is in safe state.\n");
    printf("Safe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    
    return 0;
}
