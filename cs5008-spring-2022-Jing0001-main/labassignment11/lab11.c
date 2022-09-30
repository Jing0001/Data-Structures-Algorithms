// name: Jing Feng
// email: feng.jing1@northeastern.edu
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t chopstick[5];//lock variable

// Thread to be executed
void *philosopher(void *x)
{
 //Treat variable x as a pointer to an int and then extract the value into n
    int* a=(int*)x;
    int n=*a;
    
        /*-----Insert your code here----*/
    printf("Philosopher %d is thinking.\n", n + 1);
    pthread_mutex_lock(&chopstick[n]);
    pthread_mutex_lock(&chopstick[(n + 1) % 5]);
    printf("Philosopher %d is eating using chopstick [%d] and chopstick[%d].\n", n + 1, n, (n + 1) % 5);
    sleep(1);
    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[(n + 1) % 5]);
    printf("Philosopher %d finished eating.\n", n + 1);
    
    return NULL;
}


/*------------ Main Program---------*/
int main()
{
    pthread_t threads[5];
    int i, val[5];
//initializing the mutex
    for(i = 0; i < 5; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
    }
    
//create and run the thread
    for(i = 0; i < 5; i++) {
        val[i] = i;
        pthread_create(&threads[i], NULL, (void *)philosopher, &val[i]);
    }
    
//wait until all the threads are done
    for(i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
// Destroying the mutex
    for(i = 0; i < 5; i++) {
        pthread_mutex_destroy(&chopstick[i]);
    }
    
    return 0;
}
