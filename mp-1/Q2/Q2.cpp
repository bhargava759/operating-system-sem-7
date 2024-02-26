#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 100

typedef struct {
    int buffer[MAX_BUFFER_SIZE];
    int size;
    int in;
    int out; 
    pthread_mutex_t mutex;
    pthread_cond_t empty, full;
} Buffer;

void init_buffer(Buffer *buffer, int size) {
    buffer->size = size;
    buffer->in = 0;
    buffer->out = 0;
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->empty, NULL);
    pthread_cond_init(&buffer->full, NULL);
}

void produce(Buffer *buffer, int item) {
    pthread_mutex_lock(&buffer->mutex);
    while ((buffer->in + 1) % buffer->size == buffer->out) {
        printf("Buffer is FULL. Producer waits.\n");
        pthread_cond_wait(&buffer->full, &buffer->mutex);
    }
    buffer->buffer[buffer->in] = item;
    buffer->in = (buffer->in + 1) % buffer->size;
    printf("Produced %d\n", item);
    pthread_cond_signal(&buffer->empty);
    pthread_mutex_unlock(&buffer->mutex);
}

int consume(Buffer *buffer) {
    pthread_mutex_lock(&buffer->mutex);
    while (buffer->in == buffer->out) {
        printf("Buffer is EMPTY. Consumer waits.\n");
        pthread_cond_wait(&buffer->empty, &buffer->mutex);
    }
    int item = buffer->buffer[buffer->out];
    buffer->out = (buffer->out + 1) % buffer->size;
    printf("Consumed %d\n", item);
    pthread_cond_signal(&buffer->full);
    pthread_mutex_unlock(&buffer->mutex);
    return item;
}

void *producer(void *arg) {
    Buffer *buffer = (Buffer *)arg;
    for (int i = 1; i <= 4; ++i) {
        produce(buffer, i);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    Buffer *buffer = (Buffer *)arg;
    consume(buffer); 
    sleep(2);
    return NULL;
}

int main() {
    int buffer_size;
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);

    if (buffer_size <= 0 || buffer_size > MAX_BUFFER_SIZE) {
        printf("Invalid buffer size.\n");
        return 1;
    }

    Buffer buffer;
    init_buffer(&buffer, buffer_size);

    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, &buffer);
    pthread_create(&cons_thread, NULL, consumer, &buffer);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&buffer.mutex);
    pthread_cond_destroy(&buffer.empty);
    pthread_cond_destroy(&buffer.full);

    return 0;
}

