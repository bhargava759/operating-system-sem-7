#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void printOddNumbers() {
    printf("Child 1 (PID: %d): Odd numbers: ", getpid());
    for (int i = 1; i <= 20; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

void printEvenNumbers() {
    printf("Child 2 (PID: %d): Even numbers: ", getpid());
    for (int i = 2; i <= 20; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

void printMultiplesOfThree() {
    printf("Child 3 (PID: %d): Multiples of 3: ", getpid());
    for (int i = 3; i <= 20; i += 3) {
        printf("%d ", i);
    }
    printf("\n");
}

void printMultiplesOfFive() {
    printf("Child 4 (PID: %d): Multiples of 5: ", getpid());
    for (int i = 5; i <= 20; i += 5) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    pid_t pid1, pid2, pid3, pid4;

    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid1 == 0) {
        printOddNumbers();
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid2 == 0) {
        printEvenNumbers();
        exit(0);
    }

    pid3 = fork();
    if (pid3 < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid3 == 0) {
        printMultiplesOfThree();
        exit(0);
    }

    pid4 = fork();
    if (pid4 < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid4 == 0) {
        printMultiplesOfFive();
        exit(0);
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}

