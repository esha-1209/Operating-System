#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* factorial(void* arg) {
    int n = *((int*)arg); 
    long long* result = malloc(sizeof(long long)); 
    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;  
    }

    pthread_exit((void*)result);  
}
int main() {
    pthread_t thread;
    int num;
    long long* fact_result;
    printf("Enter a number: ");
    scanf("%d", &num);
    pthread_create(&thread, NULL, factorial, &num);
    pthread_join(thread, (void**)&fact_result);
    printf("Factorial of %d is: %lld\n", num, *fact_result);
    free(fact_result);

    printf("Main thread: Work completed.\n");
    return 0;
}
