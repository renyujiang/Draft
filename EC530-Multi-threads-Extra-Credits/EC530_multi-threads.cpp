//
// Created by Renyu Jiang on 3/21/23.
//
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

// initialize global variable and mutex
int count = 0;
pthread_mutex_t mutex;

// thread worker, sleep for random seconds between 1 - 5
void *thread_func(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread %d: count = %d\n", *(int *)arg, count);
    sleep(rand() % 5 + 1);
    count++;
    printf("Thread %d: count++\n", *(int *)arg);
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

int main() {
    int thread_num=4;
    pthread_t threads[thread_num];
    int thread_ids[thread_num]; // thread id

    for(int i=0;i<thread_num;i++){
        thread_ids[i]=i;
    }

    // initialize mutex
    pthread_mutex_init(&mutex, nullptr);

    // create threads and run
    for (int i = 0; i < thread_num; i++) {
        if (pthread_create(&threads[i], nullptr, thread_func, &thread_ids[i]) != 0) {
            exit(-1);
        }
    }

    // wait for threads to complete
    for (int i = 0; i < thread_num; i++) {
        if (pthread_join(threads[i], nullptr) != 0) {
            exit(-1);
        }
    }

    printf("Threads completed\n");

    // destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
