#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_ITERATIONS 1000000

int count=10;
void critical_section(int process) {
    if(process==0){
        for (int i = 0; i < NUM_ITERATIONS; i++)
        count--;
    }
    else
    {
        for (int i = 0; i < NUM_ITERATIONS; i++)
        count++;
    }  
}
void *process0(void *arg) {
        critical_section(0);
    return NULL;
}
void *process1(void *arg) {
        critical_section(1);
    return NULL;
}
int main() {
    pthread_t thread0, thread1, thread2, thread3; 
    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process0, NULL);
    pthread_create(&thread3, NULL, process1, NULL);
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("Final count: %d\n", count);
    return 0;
}