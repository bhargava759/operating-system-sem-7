#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

int n_processes, n_resources;

bool is_safe() {
    int work[n_resources];
    bool finish[n_processes];

    // Initialize work and finish arrays
    for (int i = 0; i < n_resources; i++)
        work[i] = available[i];

    for (int i = 0; i < n_processes; i++)
        finish[i] = false;

    int count = 0;
    while (count < n_processes) {
        bool found = false;
        for (int i = 0; i < n_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < n_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < n_resources; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void request_resources(int pid, int request[]) {
    for (int i = 0; i < n_resources; i++) {
        if (request[i] > need[pid][i] || request[i] > available[i]) {
            printf("Error: Request exceeds need or available resources.\n");
            return;
        }
    }

    for (int i = 0; i < n_resources; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (is_safe()) {
        printf("Request granted.\n");
    } else {
        printf("Request denied. Reverting changes.\n");
        for (int i = 0; i < n_resources; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &n_resources);

    printf("Enter available resources:\n");
    for (int i = 0; i < n_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
        finished[i] = false;
    }

    printf("Enter allocation of resources for each process:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }

    if (is_safe()) {
        printf("Safe sequence found.\n");
    } else {
        printf("No safe sequence found.\n");
        return 1;
    }

    // Example: Process 0 requests [1, 0, 2] resources
    int request[MAX_RESOURCES];
    printf("Enter the request for resources for a process:\n");
    printf("Process ID: ");
    int pid;
    scanf("%d", &pid);
    printf("Resource request: ");
    for (int i = 0; i < n_resources; i++) {
        scanf("%d", &request[i]);
    }
    request_resources(pid, request);

    return 0;
}

