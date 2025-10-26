#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* greeting(void* arg) {
    char* name = (char*)arg;  
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    return NULL;
}
int main() {
    pthread_t thread;  
    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);
    pthread_create(&thread, NULL, greeting, (void*)name);
    printf("Main thread: Waiting for greeting...\n");
    pthread_join(thread, NULL);
    printf("Main thread: Greeting completed.\n");
    return 0;
}