// name: Jing Feng
// email: feng.jing1@northeastern.edu


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// size of graph - 10 nodes
#define GSIZE 10

// define a graph type - two dimensional array - association matrix
typedef bool graph_t[GSIZE][GSIZE];


// debug print the graph as boolean matrix
void printGraphAsMatrix(graph_t g, int size){
  int i, j;

  printf("\nGRAPH\n");

  for (i=0; i<size; i++) {
    for (j=0; j<size; j++) {
      if (g[i][j]) {
	printf("|true");
      } else {
	printf("| -- ");
      }
    }
    printf("|\n");
  }
}

// print the graph as an list of edges
void printGraphAsList(graph_t g, int size){
  int i, j;

  printf("\nGRAPH\n");

  for (i=0; i<size; i++) {
    for (j=0; j<size; j++) {
      if (g[i][j]) {
	printf("%d -> %d\n",i,j);
      } 
    }
  }
}

/*
 *   queue
 *   +--------+--------+
 *   | tail_p | head_p +----------------------------------------+
 *   +--+-----*--------+                                        |
 *      |                                                       |
 *      V                                                       V
 *   +--------+------+---------+  +--------+------+---------+  +--------+------+---------+  
 *   | left_p | data | right_p +->| left_p | data | right_p +->| left_p | data | right_p +->NULL
 *   |        |      |         |<-+        |      |         |<-+        |      |         |
 *   +--+-----+------+---------+  +--------+------+---------+  +--------+------+---------+  
 *      |       node                         node                         node
 *      V
 *      NULL
 */



//---------------------------- NODE ---------------------------- 
// doubly linked list node
typedef struct nd {
  int data;
  struct nd* left_p;
  struct nd* right_p;
} node_t;

// create new node with value d and NULL left & right pointers
node_t* newNode (int d) {
  node_t* n_p = NULL;                     // temp pointer to hold new node
  n_p = (node_t*)malloc(sizeof(node_t));  // create new node
  if (n_p != NULL) {
    n_p->data = d;                        // put data in node
    n_p->left_p = NULL;
    n_p->right_p = NULL;
  }
  return n_p;
};

// free the node pointed to by n_p
// fragile assumption: this function does not free up nodes pointed to by left/right pointers
void freeNode (node_t* n_p) {
  if (n_p != NULL) {
    free(n_p);
  }
  return;
};



//---------------------------- QUEUE  ---------------------------- 
// a queue - combining a head and a tail pointer
typedef struct q {
  node_t* head_p;
  node_t* tail_p;
} queue_t;

// create new empty queue (head and tail are set to NULL)
queue_t* newQueue() {
  queue_t* q_p;   // temp pointer to hold newly created queue
  q_p = (queue_t*)malloc(sizeof(queue_t));   // create new queue
  if (q_p != NULL) {
    q_p->head_p = NULL;
    q_p->tail_p = NULL;
  }
  return q_p;
};

// is the queue empty?
bool isEmpty(queue_t* q_p) {
  bool b = true;   // temporary bool to hold return value - initalize to default value
  if (q_p != NULL) {
    b = (q_p->head_p == NULL);
  }
  return b;
};

// function to add a new node with data d to tail of the queue
void enqueue(queue_t* q_p, int d) {
  node_t* n_p = NULL; // temp node pointer
  
  if (q_p != NULL) {

    if (isEmpty(q_p)) {
      // queue is empty so insertion is easy
      q_p->tail_p = newNode(d);  // create new node and put it in the tail
      q_p->head_p = q_p->tail_p; // in queue with 1 node, head and tail point to same ndoe
    } else {
      // queue is not empty
      n_p = q_p->tail_p;          // get a pointer to the tail fo the queue
      q_p->tail_p = newNode(d);   // create new node and put it in the tail
      n_p->left_p = q_p->tail_p;  // old tail's left pointer points back to new tail node
      q_p->tail_p->right_p = n_p; // new tail's right pointer points to old tail node
    }    
  }
  
  return;
};

// function to take the node off the head of the queue and return its value
int dequeue(queue_t* q_p) {
  int t = -9999;      // temp int to hold return val with arbitrary error value of -9999
  node_t* n_p = NULL; // temp node poitner
  
  if (q_p != NULL) {
    n_p = q_p->head_p;  // get a pointer to the head of the queue

    if (n_p != NULL) {
	t = n_p->data;      // get the value of data in the head of the queue

	if (q_p->head_p  == q_p->tail_p) {      
          // only one node in the queue, clear queue head and tail 
	  q_p->head_p = NULL;
	  q_p->tail_p = NULL;
	} else {
          // mulitple nodes in queue, clean up head pointer and new head of queue
	  q_p->head_p = n_p->left_p;   // new head points to next (left of old head) element of queue
	  q_p->head_p->right_p = NULL; // new head node has NULL right pointer
	}
	
	freeNode(n_p);  // free up the node that was dequeued
    }
  }
    
  return t;
};


// if queue is not empty, then clean it out -- then free the queue struct
void freeQueue(queue_t* q_p) {
  if (q_p != NULL) {
    // make sure the queue is empty
    while (!isEmpty(q_p)) {
      dequeue(q_p);
    }

    // free up the queue itself
    free(q_p);
  }
  return;
};


  
int main () {

  // define graph as association matrix
  graph_t E = {
    //0      1      2      3      4      5      6      7      8       9    <- destination vertex
    { false,  true, false,  true, false, false, false, false, false, false}, // vertex 0 ->
    { false, false,  true,  true,  true, false, false, false, false, false}, // vertex 1 ->
    { false, false, false, false, false,  true, false, false, false, false}, // vertex 2 ->
    { false, false, false, false,  true, false,  true, false, false, false}, // vertex 3 ->
    { false, false, false, false, false,  true,  true, false, false, false}, // vertex 4 ->
    { false, false, false, false, false, false, false, false, false, false}, // vertex 5 ->
    { false, false, false, false, false,  true, false, false,  true, false}, // vertex 6 ->
    { false, false, false, false, false,  true,  true, false, false,  true}, // vertex 7 ->
    { false, false, false, false, false, false, false, false, false,  true}, // vertex 8 ->
    { false, false, false, false, false, false, false, false, false, false}, // vertex 9 ->
  };

  queue_t* q = newQueue(); // work queue
  int i;
  int j;
  int current;
  bool done[GSIZE];   // are we done with this node?

  // initialize finsihed to false - not done with any node yet
  for (i=0; i<GSIZE; i++) {
    done[i] = false;
  }

  // debug print out the graph - as a list
  printGraphAsList(E,GSIZE);

  // add start node to work queue
  enqueue(q,0);

  printf("\nBREADTH FIRST TRAFERSAL\n");
  while (!isEmpty(q)) {

    // INSERT YOUR CODE HERE
    current = dequeue(q);
    done[current] = true;
    printf("Node: %d\n", current);
    for (int k = 0; k < GSIZE; k++) {
      if (E[current][k] == true) {
        if (!done[k]){
          enqueue(q, k);
          done[k] = true;
        }
      }
    }


  }

  // print out nodes that are unreachable
  printf("\nUNREACHABLE NODES: ");
  for (i=0; i<GSIZE; i++) {
    if (!done[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  printf("----------\n");
	 
  // free up the queue
  freeQueue(q);
  
  return 0;
}
