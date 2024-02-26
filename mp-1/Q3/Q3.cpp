#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SHARED_MEMORY_INITIAL_VALUE 10
int shared_memory = SHARED_MEMORY_INITIAL_VALUE;
sem_t semaphore1, semaphore2;
void *thread1_function(void *arg);
void *thread2_function(void *arg);
int main() {
    pthread_t thread1, thread2;
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 0); 
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    return 0;
}
void *thread1_function(void *arg) {
    int value;
    sem_wait(&semaphore1);
    value = shared_memory;
    printf("Thread 1: Doubled value: %d\n", value * 2);
    sem_post(&semaphore2);
    pthread_exit(NULL);
}
void *thread2_function(void *arg) {
    int value;
    sem_wait(&semaphore2); 
    value = shared_memory;
    printf("Thread 2: Five times value: %d\n", value * 5);
    sem_post(&semaphore1); 
    pthread_exit(NULL);
}

