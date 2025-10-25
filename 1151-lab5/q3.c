#include <stdio.h>
#include <pthread.h>
typedef struct {
int id;
char* message;
// float* value;
} ThreadData;
void* printData(void* arg) {
ThreadData* data = (ThreadData*)arg;
printf("Thread %d says: %s\n", data->id, data->message);
// printf("Thread %d value: %.2f\n", data->id, *(data->value));
return NULL;
}
int main() {
pthread_t t1, t2;
ThreadData data1 = {1, "ESHA"};
ThreadData data2 = {2, "3.00"};
pthread_create(&t1, NULL, printData, &data1);
pthread_create(&t2, NULL, printData, &data2);
pthread_join(t1, NULL);
pthread_join(t2, NULL);
printf("All threads done.\n");
return 0;
}
