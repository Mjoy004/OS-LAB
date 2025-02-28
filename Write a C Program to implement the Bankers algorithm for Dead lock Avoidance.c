#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 1024

struct Process {
    int id, arrival_time, burst_time, priority;
    int waiting_time, turnaround_time, remaining_time;
};

sem_t semaphore;

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to calculate and print results
void calculateTimes(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    printf("\nID \t AT \t BT \t WT \t TAT\n");
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf("%d \t %d \t %d \t %d \t %d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
}

// First Come First Serve (FCFS)
void FCFS(struct Process proc[], int n) {
    sem_wait(&semaphore);
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < proc[i].arrival_time)
            time = proc[i].arrival_time;
        proc[i].waiting_time = time - proc[i].arrival_time;
        time += proc[i].burst_time;
    }
    printf("\nFCFS Scheduling:");
    calculateTimes(proc, n);
    sem_post(&semaphore);
}

// Shared Memory IPC function
void sharedMemoryCommunication() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, NULL, 0);
    
    printf("\nShared Memory Communication: Writing data...\n");
    sprintf(str, "CPU Scheduling Completed Successfully");
    
    printf("Data in Shared Memory: %s\n", str);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    
    sem_init(&semaphore, 0, 1);
    
    printf("Enter process details (ID, Arrival Time, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &proc[i].id, &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].remaining_time = proc[i].burst_time;
    }
    
    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);
    
    FCFS(proc, n);
    sharedMemoryCommunication();
    
    sem_destroy(&semaphore);
    
    return 0;
}
