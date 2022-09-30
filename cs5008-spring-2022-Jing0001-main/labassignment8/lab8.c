// name: Jing Feng
// email: feng.jing1@northeastern.edu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /*structure represents a node to store the names and pointer to next node*/
typedef struct node
{
    char name[50];
    struct node* next;
}node;

/* Structure represents a Graph with an array of adjacency lists.Size of the array will be number of vertices.*/
typedef struct Graph
{
    int numberOfVertices;
    struct node** adjLists;
}Graph;

/*A function to create a newnode*/
node* createNode(char* name)
{
    node *newNode = (node *)malloc(sizeof(node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;  
}

/*A function to create a graph with an array of adjacency lists which is= numberof vertices*/
Graph* createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numberOfVertices = vertices;
    graph->adjLists = (struct node **)malloc(vertices * sizeof(struct node *));
    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL; // make adjacent lists equal to zero
    return graph;
}

/* function to count Number of listspresent in the graph */
int numberoflistspresent(Graph* graph)
{
    int i, j = 0;
    for (i = 0; i < graph->numberOfVertices; i++)
    {
        if (graph->adjLists[i] != NULL) // keeping track of how many lists are already present
            j++;
    }
    return j;
    
}
/*searching the persons who are already there in the list*/
int search(char* name, Graph* graph)
{
    int i;
    for (i = 0; i < numberoflistspresent(graph); i++)
    {
        if (strcmp(graph->adjLists[i]->name, name) == 0)
            // search for the person in the adjacent lists and if the person is found return the index of the adjlist
            return i;
    }
    return -1;
    
}
/*adds an edge to an undirected graph*/
void addConnection(Graph* graph, char* person, char* friend){
    int p = search(person, graph);//search for the person in the graph
    int n=numberoflistspresent(graph);
    
    
    
    //insert your code here
    if (n == 0){
        node * p = createNode(person);
        graph->adjLists[0] = p;
        p -> next = createNode(friend);
    }
    else {
        if (p >= 0) {
            node* temp = graph->adjLists[p];
            //node* ptr = temp;
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->next = createNode(friend);
            
        }
        if (p < 0){
            node * p = createNode(person);
            graph->adjLists[n] = p;
            node * np = createNode(friend);
            p->next = np;
        }
    }
    
    
    
}
/*function to print the adjacency list representation of a graph*/
void printGraph(Graph* graph)
{
    int i;
    for (i = 0; i<graph->numberOfVertices;i++)
    {
    //print the current vertex and all its neighbors
    struct node* temp = graph->adjLists[i];
    printf("\n%s---",graph->adjLists[i]->name );
    while((temp->next)!=NULL)
    {
    printf("%s-", temp->next->name);
    temp = temp->next;
    }
    printf("NULL\n");
    }
}

/*   CONVERSION TO MATRIX*/
int getIndex(Graph* graph, char* name)
{
    int N = graph->numberOfVertices;
    int i,j=0;
    for (i = 0; i<N&& strcmp(name,graph->adjLists[i]->name)!=0 ;i++)
    {
        j++;
    }
    return j;
}

void matrixForm(Graph* graph, int emptyMatrix[50][50],int N)
{
    int i,j;
    for (i = 0; i<N;i++){
    struct node* temp = graph->adjLists[i]->next;
    while (temp!=0)
    {
    j = getIndex(graph, temp->name);
    emptyMatrix[i][j] = 1;
    temp = temp->next;
    }
    }
}
void graphDestroy(Graph *graph)
{
    int i;
    for(i=0; i<graph->numberOfVertices;i++)
    free(graph->adjLists[i]);
    free(graph->adjLists);
        free(graph);
    }

void printMatrix(int matrix[50][50], Graph* graph)
{
    int row,col,nodes=graph->numberOfVertices;
    printf("\nAdjacent matrix:\n");
    printf("        ");
    for (col = 0; col < nodes; col++)
    {
    printf("%6s ", graph->adjLists[col]->name);
    }
    printf("\n");
    for (col = 0; col < nodes; col++)
    {
    printf("-------------");
    }
    printf("\n");
    for (row = 0; row < nodes; row++) {
    printf("%7s| ", graph->adjLists[row]->name);
    for (col = 0; col < nodes; col++) {
    printf("  %2d    ", matrix[row][col]);
    }
    printf("\n");
    }

}


int main()
{
    
    int Num=7;
    //construct a graph
    Graph* graph = createGraph(Num);
    
    addConnection(graph, "personA", "personB");
    addConnection(graph, "personA", "personG");
    addConnection(graph, "personA", "personE");
    addConnection(graph, "personB", "personA");
    addConnection(graph, "personB", "personE");
    addConnection(graph, "personB", "personC");
    addConnection(graph, "personB", "personG");
    addConnection(graph, "personC", "personB");
    addConnection(graph, "personC", "personD");
    addConnection(graph, "personC", "personE");
    addConnection(graph, "personD", "personC");
    addConnection(graph, "personD", "personE");
    addConnection(graph, "personD", "personF");
    addConnection(graph, "personE", "personA");
    addConnection(graph, "personE", "personB");
    addConnection(graph, "personE", "personC");
    addConnection(graph, "personE", "personD");
    addConnection(graph, "personE", "personF");
    addConnection(graph, "personE", "personG");
    addConnection(graph, "personF", "personE");
    addConnection(graph, "personF", "personG");
    addConnection(graph, "personF", "personD");
    addConnection(graph, "personG", "personB");
    addConnection(graph, "personG", "personA");
    addConnection(graph, "personG", "personE");
    addConnection(graph, "personG", "personF");
    //function to print the adjacency list representation of a graph
    printGraph(graph);
    /*Initialising adjacency matrix with values NULL*/
    int N = graph->numberOfVertices, i,j;
    int adj_matrix[50][50];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            adj_matrix[i][j] = 0;
        }
        
    }
    matrixForm(graph, adj_matrix, N);
    printMatrix(adj_matrix, graph);
    graphDestroy(graph);
    return 0;
}
