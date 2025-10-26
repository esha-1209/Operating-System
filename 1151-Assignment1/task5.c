#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Step 1: Define Student struct
typedef struct {
    int student_id;
    char name[50];
    float gpa;
    int on_deans_list; // to store result (1 = yes, 0 = no)
} Student;

// Step 2: Thread function
void* checkDeansList(void* arg) {
    Student* stu = (Student*)arg;

    printf("\nThread handling student: %s (ID: %d)\n", stu->name, stu->student_id);
    printf("GPA: %.2f\n", stu->gpa);

    if (stu->gpa >= 3.5) {
        printf("%s made the Dean’s List! 🎓\n", stu->name);
        stu->on_deans_list = 1;
    } else {
        printf("%s did not make the Dean’s List.\n", stu->name);
        stu->on_deans_list = 0;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    Student students[3] = {
        {101, "Alice", 3.8, 0},
        {102, "Bob", 3.2, 0},
        {103, "Charlie", 3.9, 0}
    };

    // Step 3: Create threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, checkDeansList, &students[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Step 4: Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Step 5: Main thread counts Dean’s List students
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (students[i].on_deans_list)
            count++;
    }

    printf("\nTotal students on Dean’s List: %d out of 3\n", count);

    return 0;
}