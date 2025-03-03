#include <stdio.h>
#include <limits.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    
    printf("\nFirst-Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d (%d KB) -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d (%d KB) -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    
    printf("\nWorst-Fit Allocation:\n");
    for (int i = 0; i < n; i++)
        printf("Process %d (%d KB) -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int m, n;
    
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);
    
    int tempBlockSize[MAX_BLOCKS];
    
    // First-Fit
    for (int i = 0; i < m; i++)
        tempBlockSize[i] = blockSize[i];
    firstFit(tempBlockSize, m, processSize, n);
    
    // Best-Fit
    for (int i = 0; i < m; i++)
        tempBlockSize[i] = blockSize[i];
    bestFit(tempBlockSize, m, processSize, n);
    
    // Worst-Fit
    for (int i = 0; i < m; i++)
        tempBlockSize[i] = blockSize[i];
    worstFit(tempBlockSize, m, processSize, n);
    
    return 0;
}
