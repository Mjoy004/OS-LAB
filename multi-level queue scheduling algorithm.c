#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
} Process;

void fcfs(Process queue[], int n) {
    int wait_time = 0, turnaround_time = 0;
    int completion_time[MAX_PROCESSES];
    
    printf("\nProcess Execution Order (FCFS):\n");
    for (int i = 0; i < n; i++) {
        if (i == 0)
            completion_time[i] = queue[i].arrival_time + queue[i].burst_time;
        else
            completion_time[i] = (completion_time[i - 1] > queue[i].arrival_time ? completion_time[i - 1] : queue[i].arrival_time) + queue[i].burst_time;
        
        wait_time += completion_time[i] - queue[i].arrival_time - queue[i].burst_time;
        turnaround_time += completion_time[i] - queue[i].arrival_time;
        
        printf("Process %d: Completion Time = %d\n", queue[i].pid, completion_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
}

void multiLevelQueueScheduling(Process system_queue[], int sys_n, Process user_queue[], int user_n) {
    printf("\nExecuting System Processes (Higher Priority)\n");
    fcfs(system_queue, sys_n);
    
    printf("\nExecuting User Processes (Lower Priority)\n");
    fcfs(user_queue, user_n);
}

int main() {
    Process system_queue[MAX_PROCESSES], user_queue[MAX_PROCESSES];
    int sys_n, user_n;
    
    printf("Enter number of system processes: ");
    scanf("%d", &sys_n);
    printf("Enter system process details (PID Arrival_Time Burst_Time):\n");
    for (int i = 0; i < sys_n; i++)
        scanf("%d %d %d", &system_queue[i].pid, &system_queue[i].arrival_time, &system_queue[i].burst_time);
    
    printf("Enter number of user processes: ");
    scanf("%d", &user_n);
    printf("Enter user process details (PID Arrival_Time Burst_Time):\n");
    for (int i = 0; i < user_n; i++)
        scanf("%d %d %d", &user_queue[i].pid, &user_queue[i].arrival_time, &user_queue[i].burst_time);
    
    multiLevelQueueScheduling(system_queue, sys_n, user_queue, user_n);
    
    return 0;
}
