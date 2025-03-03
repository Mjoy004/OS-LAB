#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void fifo(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], front = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    
    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            pageFaults++;
        }
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void lru(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], index[MAX_FRAMES], pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    
    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0, lruIndex = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                index[j] = i;
                break;
            }
        }
        if (!found) {
            if (i < frames) lruIndex = i;
            else {
                int min = index[0];
                for (int j = 1; j < frames; j++) {
                    if (index[j] < min) {
                        min = index[j];
                        lruIndex = j;
                    }
                }
            }
            frame[lruIndex] = pages[i];
            index[lruIndex] = i;
            pageFaults++;
        }
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void lfu(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], freq[MAX_FRAMES], pageFaults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        freq[i] = 0;
    }
    
    printf("\nLFU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0, lfuIndex = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                freq[j]++;
                break;
            }
        }
        if (!found) {
            if (i < frames) lfuIndex = i;
            else {
                int min = freq[0];
                for (int j = 1; j < frames; j++) {
                    if (freq[j] < min) {
                        min = freq[j];
                        lfuIndex = j;
                    }
                }
            }
            frame[lfuIndex] = pages[i];
            freq[lfuIndex] = 1;
            pageFaults++;
        }
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    
    fifo(pages, n, frames);
    lru(pages, n, frames);
    lfu(pages, n, frames);
    
    return 0;
}
