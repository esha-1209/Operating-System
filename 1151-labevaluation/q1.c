// Write a C program that creates 4 threads. Each thread should:
// 1.  Receive a unique number N as an argument (use values: 10, 20, 30, 40)
// 2.  Calculate the sum of numbers from 1 to N
// 3.  Print the thread number and calculated sum
// 4.  Return the sum through thread's return value
// Main thread should:
//  Create all 4 threads and pass arguments Wait for all threads to complete
//  Collect all return values
//  Calculate and print the total of all sums

#include <stdio.h>
#include <pthread.h>

int results[4];
void* calculate_sum(void* arg){
    int index =*(int*)arg;
    int N;
  if (index==0)N=10;
  else if (index==1)N=20;
  else if(index==2)N=30;
  else N=40;
  int sum=0;
  for (int i=1; i<=N; i++){
    sum+=i;
  }
  results[index]=sum;
  printf("Thread %d->%d -> Sum=%d\n",index+1, N, sum);
  pthread_exit(NULL);
  }
  int main(){
    pthread_t threads[4];
    int indices[4]={0,1,2,3};
    int total_sum=0;
    for (int i=0; i<4; i++){
        pthread_create(&threads[i], NULL, calculate_sum, &indices[i]);
    }
for (int i=0; i<4; i++){
    pthread_join(threads[i], NULL);
    total_sum+=results[i];
}
printf("\nTotal of all sums=%d\n", total_sum);
return 0;
  }


//the program creates 4 threads using the pthread library
//each thread receives a unique index that determines its value of N (10, 20, 30, 40)
//inside each thread, the sum of numbers from 1 to N is computed and stored in a global array results[].
//the main thread waits for all 4 threads to complete using pthread_join().
//finally, the main thread adds all the individual sums and prints the total sum.