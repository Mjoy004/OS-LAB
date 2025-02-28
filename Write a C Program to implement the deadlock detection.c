#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void detectDeadlock(int processes, int resources, int allocation[MAX_PROCESSES][MAX_RESOURCES], int request[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES]) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    
    bool found;
    do {
        found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while (found);
    
    bool deadlock = false;
    printf("Deadlocked processes: ");
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }
    if (!deadlock) {
        printf("None");
    }
    printf("\n");
}

int main() {
    int processes, resources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);
    
    printf("Enter allocation matrix: \n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("Enter request matrix: \n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }
    
    printf("Enter available resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }
    
    detectDeadlock(processes, resources, allocation, request, available);
    
    return 0;
}
