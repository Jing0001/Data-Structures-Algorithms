// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// size of graph - 6 nodes
#define GSIZE 6
#define INFINITY 9999

// define a graph type - two dimensional array - association matrix
typedef int graph_t[GSIZE][GSIZE];

typedef struct tr {
  int distance;     // distance from start node
  int lastStep;     // last step along the path to the start node
} trow_t;


// is the set represented by boolean array s of size "size" not empty? empty means all elements are false
bool setNotEmpty(bool s[], int size) {
  int i;
  bool result;

  result = false;
  for (i=1; i<size; i++) {
    result = result || s[i];
  }

  return result;
}

// return the row of the table (with "size" rows) with the minimum distance field - only use valid rows
int minDistance(trow_t table[], int size, bool valid[]) {
  int i;
  int vertex;
  int dist;

  vertex = -1;       // error return code
  dist = INFINITY;
  

  for (i=0; i<size; i++) {
    if (valid[i] && (table[i].distance < dist)) {
      // we found a new min distance
      vertex = i;
      dist = table[i].distance;
    }    
  }

  return vertex;
}

// find all the neighbors of v in graph g and set those values to true in array "neighbors" ("size" number of nodes)
// note that contents of array neighbors are changed by this function
void setNeighbors(bool neighbors[], graph_t g, int size, int v) {
  int i;

  for (i=0; i<size; i++) {
    if (g[v][i]>0) {
      neighbors[i] = true;
    } else {
      neighbors[i] = false;
    }
  }

  return;
}

// remove vertex v from set s
// note that array s is changed by this function
void removeVertex(int v, bool s[], int size) {
  if ((0<=v) && (v<size)) {
    s[v] = false;
  } else {
    printf("*** INVALID NODE FOUND while performing set difference\n");
  }

  return;
}


// print the distance table
void printTable(trow_t table[], int size, int start) {
  int i;
  
  printf("\nTABLE\n");

  for (i=0; i<size; i++){
    printf("[%d-%d]:%d from %d\n", start, i, table[i].distance, table[i].lastStep);
  }
    
}

// debug print the graph
void printGraph(graph_t G, int size){
  int i, j;

  printf("\nGRAPH\n");

  for (i=0; i<size; i++) {
    for (j=0; j<size; j++) {
      printf("|%0.3d", G[i][j]);
    }
    printf("|\n");
  }
}

//debug print a set
void printSet(bool s[], int size) {
  int i;

  printf("\nSET\n");

  for (i=0; i<size; i++) {
    if (s[i]) {
      printf("[%d]true ",i);
    } else {
      printf("[%d]false ",i);
    }
  }
  printf("\n");
}

  
int main () {

  // define graph as association matrix
  graph_t E = {
    //0  1  2  3  4  5   <- destination vertex
    { 0, 8,10, 0, 0,15}, // vertex 0 ->
    { 0, 0,11,16, 0, 0}, // vertex 1 ->
    { 0, 0, 0,12, 0, 3}, // vertex 2 ->
    { 0, 0, 0, 0, 0, 0}, // vertex 3 ->
    { 0, 0, 0, 7, 0, 0}, // vertex 4 ->
    { 0, 0, 0, 0,10, 0}, // vertex 5 ->
  };

  // Q is "set" of vertices - true if vertex is in set
  bool Q[GSIZE];

  // S is the "set" of neighbors of a vertex
  bool S[GSIZE];

  // T contains distance information to each node from start (0)
  trow_t T[GSIZE];

  int u; // next node being processeed
  int d; // distance variable
  int i; // loop variable
  int v; // vertext variable

  // DIJKSTRA: create table T[V] = <infinity, undefined>
  // ********** INSERT YOUR CODE HERE **********
  for (int i = 0; i < GSIZE; i++){
    T[i].distance = INFINITY;
    T[i].lastStep = -1;
  }
  // DIJKSTRA: T[source].distance = 0
  // ********** INSERT YOUR CODE HERE **********
  T[0].distance = 0;
  
  // DIJKSTRA: Create set Q = set(V)
  // ********** INSERT YOUR CODE HERE **********
  for (int i = 0; i < GSIZE; i++){
    Q[i] = true;
  }

  // DIJKSTRA: while Q is not empty
  while (setNotEmpty(Q,GSIZE)) {
    // DIJKSTRA: u = min q in Q of T[q].distance
    // ********** INSERT YOUR CODE HERE **********
    u = minDistance(T, GSIZE, Q);
    // check for errors
    if (u<0) {
      printf("*** INVALID NODE FOUND while finding min distance\n");
      return -1;
    }

    // DIJKSTRA: S = neighbors(u)
    // ********** INSERT YOUR CODE HERE **********
    setNeighbors(S, E, GSIZE, u);
    

    // DIJKSTRA: Q = Q – u
    // ********** INSERT YOUR CODE HERE **********
    removeVertex(u, Q, GSIZE);

    // DIJKSTRA: for each neighbor v of u (ignore vertices that we have already finished)
    for (v=0; v<GSIZE; v++) {
      if (S[v] && Q[v]) {
        // DIJKSTRA: d = T[u].distance + E[u,v]
        // ********** INSERT YOUR CODE HERE **********
        d = T[u].distance + E[u][v];

        // DIJKSTRA: if (d < T[v].distance)
	if (d < T[v].distance) {
  	  // DIJKSTRA: //shorter path found
  	  // DIJKSTRA: T[v].distance = d
          // ********** INSERT YOUR CODE HERE **********
          T[v].distance = d;
	  // DIJKSTRA: T[v].lastStep = u
          // ********** INSERT YOUR CODE HERE **********
          T[v].lastStep = u;
	}
      }
    }
    // DIJKSTRA: //done with u
     

  }

  printTable(T, GSIZE, 0);
   
  return 0;
}
