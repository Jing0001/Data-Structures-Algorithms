// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT 50
#define RAND_RANGE 100

int main(){

  int source[LIMIT]; // array to hold input data values
  int dest[LIMIT];   // array to hold sorted data values
                     // use dest only if you are using two arrays
  bool valid[LIMIT]; // array that indicates which input values are valid

  int i;             // loop variable
  int j;             // loop variable
  int smallest;      // current smallest element

  //seed random numbers
  srand((unsigned)time(NULL));

  //initialize valid array - at begining the full array is valid
  for (i=0; i<LIMIT; i++) {
    valid[i] = true;
  }

  //initialize source array with random numbers from 0..RAND_RANGE
  for (i=0; i<LIMIT; i++) {
    source[i] = rand() % RAND_RANGE;
  }

  //print out source array in rows of 20 elements
  printf("Source array:\n");
  for (i=0; i < ((LIMIT/20)+1); i++) {
    for (j=0; j<20; j++) {
      if (i*20+j < LIMIT) {
	printf("%.2d ",source[i*20+j]);
      }
    }
    printf("\n");
  }
  printf("\n");

  //selection sort
  for (i = 0; i < LIMIT; i++) {

    // INSERT YOUR CODE HERE
    for (j = i + 1; j < LIMIT; j++) {
      if (source[j] < source[i]) {
        int temp = source[i];
        source[i] = source[j];
        source[j] = temp;
      }
    }
  }
  
  //print out sorted array in rows of 10
  printf("Destination array:\n");
  

  // INSERT YOUR CODE HERE
  for (i=0; i < ((LIMIT/10)+1); i++) {
    for (j=0; j<10; j++) {
      if (i*10+j < LIMIT) {
	printf("%.2d ",source[i*10+j]);
      }
    }
    printf("\n");
  }
  printf("\n");
 
  
  
  return 0;
}
