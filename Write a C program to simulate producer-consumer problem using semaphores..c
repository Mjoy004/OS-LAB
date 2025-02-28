#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>

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

// Shortest Job First (SJF) - Non-preemptive
void SJF(struct Process proc[], int n) {
    sem_wait(&semaphore);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].burst_time < proc[i].burst_time) {
                swap(&proc[i], &proc[j]);
            }
        }
    }
    FCFS(proc, n);
    sem_post(&semaphore);
}

// Priority Scheduling (Non-preemptive)
void PriorityScheduling(struct Process proc[], int n) {
    sem_wait(&semaphore);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].priority < proc[i].priority) {
                swap(&proc[i], &proc[j]);
            }
        }
    }
    FCFS(proc, n);
    sem_post(&semaphore);
}

// Round Robin Scheduling (Preemptive)
void RoundRobin(struct Process proc[], int n, int quantum) {
    sem_wait(&semaphore);
    int time = 0, completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                int exec_time = (proc[i].remaining_time < quantum) ? proc[i].remaining_time : quantum;
                proc[i].remaining_time -= exec_time;
                time += exec_time;
                if (proc[i].remaining_time == 0) {
                    proc[i].waiting_time = time - proc[i].arrival_time - proc[i].burst_time;
                    completed++;
                }
            }
        }
    }
    printf("\nRound Robin Scheduling:");
    calculateTimes(proc, n);
    sem_post(&semaphore);
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
    SJF(proc, n);
    PriorityScheduling(proc, n);
    RoundRobin(proc, n, quantum);
    
    sem_destroy(&semaphore);
    
    return 0;
}
