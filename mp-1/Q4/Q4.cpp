#include <stdio.h>

#define MAX_PARTITIONS 100
#define MAX_PROCESSES 100

typedef struct {
    int size;
    int allocated;
} Partition;

typedef struct {
    int size;
    int allocated;
} Process;

void worst_fit(Partition partitions[], int m, Process processes[], int n) {
    int i, j, worst_index;
    for (i = 0; i < n; i++) {
        worst_index = -1;
        for (j = 0; j < m; j++) {
            if (!partitions[j].allocated && partitions[j].size >= processes[i].size) {
                if (worst_index == -1 || partitions[j].size > partitions[worst_index].size) {
                    worst_index = j;
                }
            }
        }
        if (worst_index != -1) {
            partitions[worst_index].allocated = 1;
            processes[i].allocated = 1;
            int remaining_space = partitions[worst_index].size - processes[i].size;
            printf("+------------+------------+-------------------+\n");
            printf("| Process    | Partition  | Remaining Space   |\n");
            printf("+------------+------------+-------------------+\n");
            printf("| %-10d | %-10d | %-13d |\n", processes[i].size, partitions[worst_index].size, remaining_space);
            printf("+------------+------------+-------------------+\n");
        } else {
            printf("+------------+------------+-------------------+\n");
            printf("| Process    | Partition  | Remaining Space   |\n");
            printf("+------------+------------+-------------------+\n");
            printf("| %-10d | %-10s | %-13s |\n", processes[i].size, "Not Allocated", "");
            printf("+------------+------------+-------------------+\n");
        }
    }
}

int main() {
    Partition partitions[MAX_PARTITIONS];
    Process processes[MAX_PROCESSES];
    int num_partitions, num_processes, i;

    printf("Enter the number of memory partitions: ");
    scanf("%d", &num_partitions);

    printf("Enter sizes of memory partitions (in KB):\n");
    for (i = 0; i < num_partitions; i++) {
        printf("Partition %d: ", i + 1);
        scanf("%d", &partitions[i].size);
        partitions[i].allocated = 0;
    }

    printf("\nEnter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter sizes of processes (in KB):\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].allocated = 0;
    }

    printf("\nWorst-Fit Allocation:\n");
    worst_fit(partitions, num_partitions, processes, num_processes);

    return 0;
}

