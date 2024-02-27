#include <stdio.h>

#define MAX_PARTITIONS 100
#define MAX_PROCESSES 100

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES] = {-1};
    int fragment[MAX_PARTITIONS];

    for (int i = 0; i < m; i++)
        fragment[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
        printf(" %d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1);

    printf("\nRemaining memory blocks:\n");
    for (int i = 0; i < m; i++)
        printf("Block %d: %d\n", i + 1, blockSize[i]);
}

int main() {
    int m, n;
    int blockSize[MAX_PARTITIONS], processSize[MAX_PROCESSES];

    printf("Enter the number of memory partitions: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the sizes of memory partitions:\n");
    for (int i = 0; i < m; i++) {
        printf("Size of block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Size of process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}

