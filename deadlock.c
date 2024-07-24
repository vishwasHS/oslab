#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 20

int n, m;                                                 
int alloc[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int avail[MAX_RESOURCES];
bool finish[MAX_PROCESSES];
bool visited[MAX_PROCESSES];

void input()
{
    printf("Enter the number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    printf("Enter the matrix of current allocation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the matrix of maximum allocation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
}

void initialize()
{
    for (int i = 0; i < n; i++) {
        finish[i] = false;
        visited[i] = false;
    }
}

bool can_allocate(int process, int resources[])
{
    for (int i = 0; i < m; i++) {
        if (resources[i] > avail[i])
            return false;
    }
    return true;
}

void mark_safe(int process)
{
    visited[process] = true;
    for (int i = 0; i < m; i++) {
        avail[i] += alloc[process][i];
    }
}

void deadlock_detection()
{
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (!finish[i] && can_allocate(i, alloc[i])) {
            mark_safe(i);
            found = true;
            break;
        }
    }

    if (!found) {
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                printf("Deadlock detected at process %d\n", i);
                return;
            }
        }
        printf("No deadlock detected\n");
    }
}

int main()
{
    input();
    initialize();
    deadlock_detection();
    return 0;
}
