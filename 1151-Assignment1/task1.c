#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()

// Thread function
void* threadFunction(void* arg) {
    int threadNum = *(int*)arg; // get thread number
    pthread_t tid = pthread_self(); // get thread ID
    
    printf("Thread %d started. Thread ID: %lu\n", threadNum, tid);

    // sleep for 1–3 seconds randomly
    int sleepTime = (rand() % 3) + 1;
    sleep(sleepTime);

    printf("Thread %d (ID: %lu) completed after %d seconds.\n",
           threadNum, tid, sleepTime);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int threadNums[5];

    srand(time(NULL)); // seed random generator

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        threadNums[i] = i + 1; // thread number 1–5
        if (pthread_create(&threads[i], NULL, threadFunction, &threadNums[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}
