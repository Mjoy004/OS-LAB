#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
sem_t mutex;
sem_t chopstick[N];

void test(int phil) {
    if (state[phil] == HUNGRY && state[(phil + 4) % N] != EATING && state[(phil + 1) % N] != EATING) {
        state[phil] = EATING;
        printf("Philosopher %d is eating\n", phil);
        sleep(1);
        sem_post(&chopstick[phil]);
    }
}

void take_fork(int phil) {
    sem_wait(&mutex);
    state[phil] = HUNGRY;
    printf("Philosopher %d is hungry\n", phil);
    test(phil);
    sem_post(&mutex);
    sem_wait(&chopstick[phil]);
    sleep(1);
}

void put_fork(int phil) {
    sem_wait(&mutex);
    state[phil] = THINKING;
    printf("Philosopher %d is thinking\n", phil);
    test((phil + 4) % N);
    test((phil + 1) % N);
    sem_post(&mutex);
}

void *philosopher(void *num) {
    int *i = (int *)num;
    while (1) {
        sleep(1);
        take_fork(*i);
        sleep(1);
        put_fork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    int phil[N] = {0, 1, 2, 3, 4};

    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 0);

    for (i = 0; i < N; i++)
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    
    return 0;
}
