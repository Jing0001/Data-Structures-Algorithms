// name: Jing Feng
// email: feng.jing1@northeastern.edu
// Compile with:
//
// gcc -lpthread hw12.c -o hw12
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 100
// NOTE se are going to adapt the 100 thread code
// by making the array bigger
// and spawning off 4 groups of 100 threads

// shared variable
int counter = 0;

// thread to be executed - unspecified variable arguments
void* thread1 (void* vargp) {
  // add 1 to counter
  counter = counter +1;
  return NULL;
}

void* thread2 (void* vargp) {
  // add 5 to counter
  // *** YOUR CODE GOES HERE ***
  counter = counter + 5;
  return NULL;
}

void* thread3 (void* vargp) {
  // subtract 2 from counter
  // *** YOUR CODE GOES HERE ***
  counter = counter - 2;
  return NULL;
}

void* thread4 (void* vargp) {
  // subtract 10 from counter
  // *** YOUR CODE GOES HERE ***
  counter = counter - 10;
  return NULL;
}

int main() {
  // array to keep Pthread IDs of created threads
  pthread_t tid[NTHREADS*4];
  int i;

  printf("Counter starts at %d\n", counter);
  
  // create and run the thread
  for (i=0; i < NTHREADS; ++i){
    // create the first 100 threads using thread1 code
    pthread_create(&(tid[i]), NULL, thread1, NULL);

    // now create the 2nd, 3rd, 4th group of 100 threads
    
    // *** YOUR CODE GOES HERE ***
    pthread_create(&(tid[i + NTHREADS]), NULL, thread2, NULL);
    pthread_create(&(tid[i + 2 * NTHREADS]), NULL, thread3, NULL);
    pthread_create(&(tid[i + 3 * NTHREADS]), NULL, thread4, NULL);
  }

  //wait until ALL 400 threads are done
  for (i=0; i < NTHREADS*4; ++i){
    pthread_join(tid[i], NULL);
  }

  printf("Counter ends at %d\n", counter);

  return 0;
}
