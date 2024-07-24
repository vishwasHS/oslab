#include<stdio.h>
#include<stdbool.h>
void calculate_need(int n, int m, int alloc[20][20], int max[20][20], int need[20][20])
{
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Print need matrix
    printf("Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
bool banker(voint n, int m, int alloc[20][20], int max[20][20], int need[20][20])

    
