// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 50

//define a structure for queue
typedef struct
{
    int a[MAX];
    int front,rear;
}Queue;

//isEmpty function
int isEmpty(int front)
{
    if(front==-1)
        return 1;
    else
        return 0;
}

//Dequeue function to dequeue a vertex from the queue*/
int dequeue(Queue *q)
{
    
    int x=q->a[q->front];
    if(q->front==q->rear)
    {
        q->front=q->rear=-1;
    }
    else
     {
         q->front++;
     }
    return x;
}
/* Queue to hold the vertices with in-degree zero*/
void enqueue(Queue *q, int e)
{

    q->rear++;
    q->a[q->rear]=e;
    if(q->front==-1)
    {
        q->front=0;
    }
}

/*Create graph in adjacency matrix form*/
void creategraph(int arr[][MAX],int V)
{
    int i,j;
    for(i =1; i<=V; i++)
    {
        for(j = 1; j<=V; j++)
        {
            arr[i][j] = 0;
        }
    }
}

/* Function to add edges from source to destination*/
void addEdge(int arr[][MAX],int src, int dest)
{
     arr[src][dest] = 1;
}

/*Print the adjacency matrix of the Graph*/
void printAdjMatrix(int arr[][MAX],int V)
{
     int i, j;

     for(i =1; i<=V; i++)
     {
         for(j = 1; j<=V; j++)
         {
             printf("%6d ", arr[i][j]);
         }
         printf("\n");
     }
}
/*calculate the indegree of each vertex by looping through all vertices and edges in the adjacency matrix*/
int find_indegree(int arr[][MAX], int node)
{
    int i,in_deg = 0;
    int n=7;
    for(i=1;i<=n;i++)
    {
        if(arr[i][node]==1)
            in_deg++;
    }
    return in_deg;
    
    
}
/*Function to perform topological sorting of the Graph */
void topologicalOrder(int arr[][MAX], Queue *t, int n)
{
    int j=0,delNode,i;
    int result[MAX],indeg[MAX];
    for(i=1;i<=n;i++)
    {
        indeg[i]=find_indegree(arr,i);
        if(indeg[i]==0)
            enqueue(t,i);
    }
    
    
    
    //insert your code here
    while (isEmpty(t->front) == false){
        result[j] = delNode = dequeue(t);
        j++;
        for(i=1;i<=n;i++){
            if (arr[delNode][i] == 1){
                arr[delNode][i] = 0;
                indeg[i]--;
                if (indeg[i] == 0){
                    enqueue(t, i);
                }
            }
        }
    }

    
    
    printf("topological ordering\n");
    for(i=0; i<j;i++)
        printf("%d\t",result[i]);
    printf("\n");
    
}
/*Main Program*/
int main()
{
    int adjMatrix[MAX][MAX];
    int vertices=7;
    Queue t;
    t.front=t.rear=-1;
    creategraph(adjMatrix,vertices);
    addEdge(adjMatrix,1,2);
    addEdge(adjMatrix,2,3);
    addEdge(adjMatrix,2,5);
    addEdge(adjMatrix,2,4);
    addEdge(adjMatrix,3,5);
    addEdge(adjMatrix,4,5);
    addEdge(adjMatrix,5,6);
    addEdge(adjMatrix,7,4);
    
    printAdjMatrix(adjMatrix,vertices);
    topologicalOrder(adjMatrix, &t,vertices);
   
    return 0;
}
