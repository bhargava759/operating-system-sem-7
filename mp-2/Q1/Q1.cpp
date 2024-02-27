#include <stdio.h>

void calculate_waiting_times(int n, int bt[], int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void calculate_turnaround_times(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void calculate_average_times(int n, int bt[]) {
    int wt[n], tat[n];
    float total_wt = 0, total_tat = 0;

    calculate_waiting_times(n, bt, wt);
    calculate_turnaround_times(n, bt, wt, tat);

    printf("+---------------+-------------+----------------+---------------+\n");
    printf("| Process ID    | Burst Time  | Waiting Time  | Turnaround Time |\n");
    printf("+---------------+-------------+----------------+---------------+\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("| %13d | %11d | %14d | %14d |\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("+---------------+-------------+----------------+---------------+\n");

    printf("+-------------------------------+---------------+\n");
    printf("| Average Waiting Time          | %14.2f |\n", total_wt / n);
    printf("+-------------------------------+---------------+\n");

    printf("+-------------------------------+---------------+\n");
    printf("| Average Turnaround Time       | %14.2f |\n", total_tat / n);
    printf("+-------------------------------+---------------+\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("\nFCFS Scheduling (Adverse Version):\n");
    calculate_average_times(n, burst_time);

    return 0;
}

