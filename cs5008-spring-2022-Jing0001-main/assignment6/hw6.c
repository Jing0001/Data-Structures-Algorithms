// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING 200

// ========================== TREE DEFINITIONS ==========================
// define tree node structure 
typedef struct tnd {
  char data;
  struct tnd* left;
  struct tnd* right;
} tnode_t;

// "new" function to create a tree node, set data value to d and childrent to NULL
tnode_t* newTNode(char d) {
  tnode_t* np;
  np = (tnode_t*)malloc(sizeof(tnode_t));
  if (np != NULL) {
    np->data = d;
    np->left = NULL;
    np->right = NULL;
  }
  return(np);
}

// free a tree node and all its children
void freeTNode(tnode_t* np) {
  if (np != NULL) {
    freeTNode(np->left);
    freeTNode(np->right);
    free(np);
  }
}


// ========================== STRING MANIPULATION - EXTRACT FIRST CHARACTER  ==========================

// remove the first character from string s and return it
// \x01 will be an error code if string is empty
char getFirstChar(char* s) {
  char c;
  if (strlen(s) > 0) {
    // copy the first character
    c = s[0];

    // remove the first charcter from the string - memmove comes from the string.h library
    memmove(s, s+1, strlen(s));
  } else {
    // empty string, set error code
    c = '\x01';
  }

  return c;
}

// ========================== MAIN RECURSIVE FUNCTION TO BUILD TREE  ==========================
// using the instruction in string s, insert the defined tree nodes into tree pointed to by rp
void insertTNode (tnode_t* rp, char* s) {
  char c;   // temporary character

  // we assume that rp points to an existing tree node and
  // we are going to add its two children based on the next two instructions in s
  if (rp != NULL) {
  
    // if instruction string is not empty then add a new tree node to the left
    if (strlen(s) >  0) {        
      // get the first character of the string which is our "instruction"
      c = getFirstChar(s);

      if (c == '\x01') {
	printf("ILLEGAL CHARACTER IN INSTRUCTION STRING\n");
      }
      
      // if instruction does not tell us to insert null, create a new tree node and add it as left child, recurse
      if (c != '\n') {
	rp->left = newTNode(c);
	insertTNode(rp->left, s);
      }    
    }

    // if instruction string is not empty then add a new tree node to the right
    if (strlen(s) >  0) {       
      // get the first character of the string which is our "instruction"
      c = getFirstChar(s);

      if (c == '\x01') {
	printf("ILLEGAL CHARACTER IN INSTRUCTION STRING\n");
      }

      // if instruction does not tell us to insert null, create a new tree node and add it as right child, recurse
      if (c != '\n') {
	rp->right = newTNode(c);
	insertTNode(rp->right, s);
      }   
    }
  }
  return;
}


// ========================== QUEUE DEFINITIONS ==========================

//---------------------------- QUEUE NODES ---------------------------- 
// queue built of doubly linked list nodes
typedef struct qnd {
  tnode_t* tnode;
  struct qnd* left;
  struct qnd* right;
} qnode_t;

// create new queue node with value (tree node) d and NULL left & right pointers
qnode_t* newQNode (tnode_t* d) {
  qnode_t* np = NULL;                     // temp pointer to hold new queue node
  np = (qnode_t*)malloc(sizeof(qnode_t));  // create new node
  if (np != NULL) {
    np->tnode = d;                        // put tree node pointer in queue node
    np->left = NULL;
    np->right = NULL;
  }
  return np;
};

// free the node pointed to by np
// frees only the current node!
void freeQNode (qnode_t* np) {
  if (np != NULL) {
    free(np);
  }
  return;
};



//---------------------------- QUEUE  ---------------------------- 
// a queue - combining a head and a tail pointer
typedef struct qq {
  qnode_t* head;
  qnode_t* tail;
} queue_t;

// create new empty queue (head and tail are set to NULL)
queue_t* newQueue() {
  queue_t* qp;   // temp pointer to hold newly created queue
  qp = (queue_t*)malloc(sizeof(queue_t));   // create new queue
  if (qp != NULL) {
    qp->head = NULL;
    qp->tail = NULL;
  }
  return qp;
};

// is the queue empty?
bool isEmpty(queue_t* qp) {
  bool b = true;   // temporary bool to hold return value - initalize to default value
  if (qp != NULL) {
    b = (qp->head == NULL);

    // check to make if head is null that tail is null too
    if (b && (qp->tail != NULL)) {
      printf("ERROR Queue is NOT empty, but head is NULL!\n");
    }
  }
  return b;
};

// function to add a new queue node with tree node pointer d to tail of the queue
void enqueue(queue_t* qp, tnode_t* d) {
  qnode_t* np = NULL; // temp queue node pointer
  
  if (qp != NULL) {

    if (isEmpty(qp)) {
      // queue is empty so insertion is easy
      qp->tail = newQNode(d);  // create new node and put it in the tail
      qp->head = qp->tail; // in queue with 1 node, head and tail point to same ndoe
    } else {
      // queue is not empty
      np = qp->tail;          // get a pointer to the tail fo the queue
      qp->tail = newQNode(d);   // create new node and put it in the tail
      np->left = qp->tail;  // old tail's left pointer points back to new tail node
      qp->tail->right = np; // new tail's right pointer points to old tail node
    }    
  }
  
  return;
};

// function to take the node off the head of the queue and return its value
tnode_t* dequeue(queue_t* qp) {
  tnode_t* tp = NULL;    // temp tree node pointer
  qnode_t* np = NULL; // temp queue node poitner
  
  if (qp != NULL) {
    np = qp->head;  // get a pointer to the head of the queue

    if (np != NULL) {
	tp = np->tnode;      // get the value of data (tree node) in the head of the queue

	if (qp->head  == qp->tail) {      
          // only one node in the queue, clear queue head and tail 
	  qp->head = NULL;
	  qp->tail = NULL;
	} else {
          // mulitple nodes in queue, clean up head pointer and new head of queue
	  qp->head = np->left;   // new head points to next (left of old head) element of queue
	  qp->head->right = NULL; // new head node has NULL right pointer
	}
	
	freeQNode(np);  // free up the queue node that was dequeued
    }
  }
    
  return tp;    // return the tree node from the head of the queue
};


// if queue is not empty, then clean it out -- then free the queue struct
void freeQueue(queue_t* qp) {
  if (qp != NULL) {
    // make sure the queue is empty
    while (!isEmpty(qp)) {
      dequeue(qp);
    }

    // free up the queue itself
    free(qp);
  }
  return;
};


// ========================== BEGIN INSERT FUNCTION DEFS TO WALK TREE ==========================
// define 4 functions - preorder, inorder, postorder, breadthFirst to walk tree, printing out data (char)
// associated with each node visited:
// void preorder (tnode_t* np) {}
// void inorder (tnode_t* np) {}
// void postorder (tnode_t* np) {}
// void breadthFirst (tnode_t* np) {}

void preorder (tnode_t* np) {
  // INSERT YOUR CODE HERE
  if (np == NULL) {
    return;
  }
  printf("%c", np->data);
  preorder (np->left);
  preorder (np->right);
  return;
}

void inorder (tnode_t* np) {
  // INSERT YOUR CODE HERE
  if (np == NULL) {
    return;
  }
  inorder (np->left);
  printf("%c", np->data);
  inorder (np->right);
  return;
}

void postorder (tnode_t* np) {
  // INSERT YOUR CODE HERE
  if (np == NULL) {
    return;
  }
  postorder (np->left);
  postorder (np->right);
  printf("%c", np->data);
  return;
}


void breadthFirst (tnode_t* root) {
  // INSERT YOUR CODE HERE
  tnode_t* temp = NULL;
  queue_t* newQ =  newQueue();
  if (root != NULL) {
    enqueue(newQ, root);
    while (!isEmpty(newQ)) {
      temp = dequeue(newQ);
      printf("%c", temp->data);
      if (temp->left != NULL) {
        enqueue(newQ, temp->left);
      }
      if (temp->right != NULL) {
        enqueue(newQ, temp->right);
      }
    }
  }
  return;
}



// ========================== END INSERT FUNCTIONS HERE TO WALK TREE ==========================




// ========================== MAIN PROGRAM  ==========================
int main() {
  char c;                // temporary character variable
  tnode_t* rootp;         // root of our binary tree
  
  // dna is a string defining the content and structure of the tree in pre-order with '\n' for NULL pointers
  char dna[MAX_STRING] = "ABDHP\n\nQ\n\nIR\n\nS\n\nEJT\n\nU\n\nKV\n\nW\n\nCFL\n\nMX\n\nY\n\nGN\nZ\n\nO\n\n";

  
  // prime the pump - add the first node to the tree and then recursively call on children
  rootp = NULL;
     
  // if instruction string is not empty then create root node
  if (strlen(dna) >  0) {    
    // get the first character of the string which is our "instruction"
    c = getFirstChar(dna);

    if (c == '\x01') {
      printf("ILLEGAL CHARACTER IN INSTRUCTION STRING\n");
    }
      
    // if instruction does not tell us to insert null, create a new node and add it as left child, recurse
    if (c != '\n') {
      rootp = newTNode(c);
      insertTNode(rootp, dna);
    }    
  }

  // ========================== MAIN PROG CODE TO CALL WALK FUNCTONS  ==========================
  
  printf("PREORDER:\n");
  preorder(rootp);
  printf("\n\n");

  printf("INORDER:\n");
  inorder(rootp);
  printf("\n\n");

  printf("POSTORDER:\n");
  postorder(rootp);
  printf("\n\n");

  printf("BREADTH FIRST:\n");
  breadthFirst(rootp);
  printf("\n\n");

  freeTNode(rootp);

  return 0;
}





