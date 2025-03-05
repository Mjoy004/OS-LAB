#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

// Structure for a file
typedef struct {
    int startBlock;
    int length;
    int blocks[MAX_BLOCKS]; // For indexed allocation
} File;

File files[MAX_FILES];
int disk[MAX_BLOCKS] = {0};
int fileCount = 0;

void sequentialAllocation() {
    int start, length, i;
    if (fileCount >= MAX_FILES) {
        printf("File limit reached!\n");
        return;
    }
    
    printf("Enter starting block and length of file: ");
    scanf("%d %d", &start, &length);
    
    for (i = start; i < start + length; i++) {
        if (disk[i] == 1) {
            printf("Block %d is already allocated. File cannot be stored sequentially!\n", i);
            return;
        }
    }
    
    for (i = start; i < start + length; i++) disk[i] = 1;
    files[fileCount].startBlock = start;
    files[fileCount].length = length;
    fileCount++;
    printf("File allocated successfully in sequential manner.\n");
}

void indexedAllocation() {
    int indexBlock, numBlocks, i;
    if (fileCount >= MAX_FILES) {
        printf("File limit reached!\n");
        return;
    }
    
    printf("Enter index block and number of blocks: ");
    scanf("%d %d", &indexBlock, &numBlocks);
    
    if (disk[indexBlock] == 1) {
        printf("Index block already occupied!\n");
        return;
    }
    disk[indexBlock] = 1;
    files[fileCount].startBlock = indexBlock;
    files[fileCount].length = numBlocks;
    
    printf("Enter %d block numbers: ", numBlocks);
    for (i = 0; i < numBlocks; i++) {
        scanf("%d", &files[fileCount].blocks[i]);
        if (disk[files[fileCount].blocks[i]] == 1) {
            printf("Block %d is already allocated!\n", files[fileCount].blocks[i]);
            return;
        }
        disk[files[fileCount].blocks[i]] = 1;
    }
    fileCount++;
    printf("File allocated successfully using indexed allocation.\n");
}

void linkedAllocation() {
    int start, length, i, block;
    if (fileCount >= MAX_FILES) {
        printf("File limit reached!\n");
        return;
    }
    
    printf("Enter starting block and number of blocks: ");
    scanf("%d %d", &start, &length);
    
    if (disk[start] == 1) {
        printf("Starting block is already allocated!\n");
        return;
    }
    disk[start] = 1;
    files[fileCount].startBlock = start;
    files[fileCount].length = length;
    
    printf("Enter %d block numbers: ", length - 1);
    for (i = 0; i < length - 1; i++) {
        scanf("%d", &block);
        if (disk[block] == 1) {
            printf("Block %d is already allocated!\n", block);
            return;
        }
        disk[block] = 1;
        files[fileCount].blocks[i] = block;
    }
    fileCount++;
    printf("File allocated successfully using linked allocation.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nFile Allocation Strategies\n");
        printf("1. Sequential Allocation\n");
        printf("2. Indexed Allocation\n");
        printf("3. Linked Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: sequentialAllocation(); break;
            case 2: indexedAllocation(); break;
            case 3: linkedAllocation(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
