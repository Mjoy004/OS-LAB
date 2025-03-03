#include <stdio.h>

#define MAX_PAGES 100
#define MAX_FRAMES 50

int main() {
    int pageTable[MAX_PAGES];
    int numPages, numFrames, pageSize, memSize;
    int logicalAddr, pageNumber, offset, frameNumber, physicalAddr;

    // Input memory and paging details
    printf("Enter total memory size (in KB): ");
    scanf("%d", &memSize);
    printf("Enter page size (in KB): ");
    scanf("%d", &pageSize);
    
    numPages = memSize / pageSize;
    printf("Enter number of frames available: ");
    scanf("%d", &numFrames);
    
    if (numFrames > numPages) {
        printf("Number of frames cannot exceed total pages. Limiting to %d.\n", numPages);
        numFrames = numPages;
    }

    // Initialize page table (Random frame allocation for simplicity)
    printf("Enter frame numbers for each page (-1 for unmapped pages):\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    // Address translation
    printf("Enter a logical address: ");
    scanf("%d", &logicalAddr);
    
    pageNumber = logicalAddr / pageSize;
    offset = logicalAddr % pageSize;
    
    if (pageNumber >= numPages || pageTable[pageNumber] == -1) {
        printf("Invalid access! Page not mapped in memory.\n");
    } else {
        frameNumber = pageTable[pageNumber];
        physicalAddr = (frameNumber * pageSize) + offset;
        printf("Logical Address: %d -> Physical Address: %d\n", logicalAddr, physicalAddr);
    }
    
    return 0;
}
