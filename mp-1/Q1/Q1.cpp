#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    char pid[3];  
    int burst_time;  
    int remaining_time; 
    int waiting_time;  
    int turnaround_time;  
} Process;

void round_robin(Process processes[], int n, int quantum) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int time = 0;
    int i, done;

    while (1) {
        done = 1;
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0;
                if (processes[i].remaining_time > quantum) {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    total_waiting_time += processes[i].waiting_time;
                    processes[i].turnaround_time = time;
                    total_turnaround_time += processes[i].turnaround_time;
                }
            }
        }
        if (done)
            break;
    }

    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("+---------+------------+--------------+----------------+\n");
        printf("|   %s\t   |     %d\t   |      %d\t   |        %d\t    |\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("+---------+------------+--------------+----------------+\n");

    printf("\nAverage Waiting Time: %.2f ms\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f ms\n", avg_turnaround_time);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n, quantum, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        sprintf(processes[i].pid, "P%d", i + 1);
    }

    printf("Enter the quantum time slot: ");
    scanf("%d", &quantum);

    round_robin(processes, n, quantum);

    return 0;
}

