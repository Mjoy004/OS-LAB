#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void fcfs(int requests[], int n, int head) {
    int seek_count = 0;
    printf("\nFCFS Disk Scheduling:\n");
    printf("Seek sequence: %d", head);
    for (int i = 0; i < n; i++) {
        seek_count += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal seek time: %d\n", seek_count);
}

void scan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0, direction;
    printf("\nSCAN Disk Scheduling:\n");
    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);
    
    requests[n] = 0; // Add start boundary
    requests[n + 1] = disk_size - 1; // Add end boundary
    n += 2;
    
    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    
    int index;
    for (index = 0; index < n; index++) {
        if (requests[index] > head)
            break;
    }
    
    printf("Seek sequence: %d", head);
    if (direction == 1) { // Move right
        for (int i = index; i < n; i++) {
            seek_count += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
        for (int i = index - 1; i >= 0; i--) {
            seek_count += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
    } else { // Move left
        for (int i = index - 1; i >= 0; i--) {
            seek_count += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
        for (int i = index; i < n; i++) {
            seek_count += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal seek time: %d\n", seek_count);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0;
    printf("\nC-SCAN Disk Scheduling:\n");
    
    requests[n] = 0; // Start boundary
    requests[n + 1] = disk_size - 1; // End boundary
    n += 2;
    
    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    
    int index;
    for (index = 0; index < n; index++) {
        if (requests[index] > head)
            break;
    }
    
    printf("Seek sequence: %d", head);
    for (int i = index; i < n; i++) {
        seek_count += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    for (int i = 0; i < index; i++) {
        seek_count += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal seek time: %d\n", seek_count);
}

int main() {
    int n, head, disk_size, choice;
    int requests[MAX_REQUESTS];
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    
    while (1) {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FCFS\n2. SCAN\n3. C-SCAN\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: fcfs(requests, n, head); break;
            case 2: scan(requests, n, head, disk_size); break;
            case 3: cscan(requests, n, head, disk_size); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
