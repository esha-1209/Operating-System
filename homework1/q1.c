#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_lock;

void* producer(void* arg) {
    int producer_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        int item = producer_id * 100 + i + 1;
        
        // Wait until an empty slot is available
        sem_wait(&empty_slots);
        
        // Lock the buffer for exclusive access
        pthread_mutex_lock(&buffer_lock);
        
        buffer[in] = item;
        printf("[PRODUCER %d] Produced item %d at buffer index %d\n", 
               producer_id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        
        // Release buffer lock
        pthread_mutex_unlock(&buffer_lock);
        
        // Signal that a new item is available
        sem_post(&full_slots);
        
        sleep(1);  // Simulate production delay
    }
    
    return NULL;
}

void* consumer(void* arg) {
    int consumer_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        // Wait until a filled slot is available
        sem_wait(&full_slots);
        
        // Lock the buffer before consuming
        pthread_mutex_lock(&buffer_lock);
        
        int item = buffer[out];
        printf("[CONSUMER %d] Consumed item %d from buffer index %d\n", 
               consumer_id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        
        // Release buffer lock
        pthread_mutex_unlock(&buffer_lock);
        
        // Signal that a buffer slot is now free
        sem_post(&empty_slots);
        
        sleep(2);  // Simulate consumption delay
    }
    
    return NULL;
}

int main() {
    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {1, 2};
    int consumer_ids[2] = {1, 2};
    
    // Initialize semaphores and mutex
    sem_init(&empty_slots, 0, BUFFER_SIZE);  // Initially, all buffer slots are empty
    sem_init(&full_slots, 0, 0);             // No items available initially
    pthread_mutex_init(&buffer_lock, NULL);
    
    // Create producer and consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }
    
    // Wait for all threads to complete execution
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }
    
    // Destroy semaphores and mutex
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_lock);
    
    printf("\nAll producer and consumer threads have completed execution successfully.\n");
    return 0;
}
