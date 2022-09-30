// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include<stdio.h>
#include<stdlib.h>
/*----defining the structure for Avl tree node----*/
typedef struct avlnode
{
    int data;
    struct avlnode *left;
    struct avlnode *right;
    int height;
} node_t;
/*---defining structure for AVL tree--*/
typedef struct AVL{
    struct avlnode* root;
}Tree;

/* creating a new Avl node*/
node_t* NewNode(int data){

    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 0;
    return temp;
}
/*------------Creating a Tree------------------*/
Tree* initTree(){
    Tree* t;
    t=(Tree*)malloc(sizeof(Tree));
    if(t==NULL){
     printf("Memory is not allocated\n");
     exit(1);
 }
    t->root=NULL;
    
    return t;
}


/* calculating maximum of 2 numbers*/
int max(int a,int b){

     if(a>b)
         return a;
 else return b;
}

/* finding the height of the tree*/
int height(node_t* node){

    if(node==NULL)
        return -1;

     return node->height;
}

/* finding the balance factor of the node*/
int Balance(node_t* node){

    if(node==NULL)
        return 0;

     return height(node->left) - height(node->right);//height of Left subtree-height of right subtree.
}

/* left rotation of the node and updating the height of left and right subtree*/
node_t* LeftRotate(node_t* z){

    node_t* y = z->right;
    node_t* temp = y->left;

    y->left = z;
    z->right = temp;

    z->height = max(height(z->left),height(z->right))+1;
    y->height = max(height(y->left),height(y->right))+1;

    return y;
}

/*--- function to perform the Right rotation and updating the height of left and right subtree--*/
node_t* RightRotate(node_t *z){

    node_t* y = z->left;
    node_t* temp = y->right;

    y->right = z;
    z->left = temp;
/*update the height after right rotation*/
    z->height = max(height(z->left),height(z->right))+1;
    y->height = max(height(y->left),height(y->right))+1;

    return y;
}

/*---------------- function to display the preorder traversal of AVL tree------------*/
void preorder(node_t *temp){
    
    
    if(temp!=NULL)
    {
    printf("%d\n",temp->data);
    preorder(temp->left);
    preorder(temp->right);
      
    }
}
/*---free the AVL nodes----*/
void freenode(node_t *p){

    if(p!=NULL)
    {
        freenode(p->left);
        freenode(p->right);
        free(p);
    }
}

/* ----------------function to insert a node*---------------------------*/
/* Insert a node like a Binary search tree, then convert it into a AVL tree using four cases*/
node_t* Insert(node_t* root, int data)
{

    
    
    //insert your code here
    if (root == NULL) {
        return NewNode(data);
    }

    if (data < root->data) {
        root->left = Insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = Insert(root->right, data);
    }
    else {
        return root;
    }

/*updating the height after insertion of the node*/
    root->height = max(height(root->left),height(root->right))+1;
    
/*checking the balance factor to check the tree is balanced */
    int balance = Balance(root);

    /* left- left case*/
    if(balance > 1 && data < root->left->data)
        return RightRotate(root);

    /* Right Right Case*/
    if(balance < -1 && data > root->right->data)
        return LeftRotate(root);

    /*Left Right Case*/
    if(balance > 1 && data > root->left->data)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    /* Right Left Case*/
    if(balance < -1 && data < root->right->data)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}



/*------------------main program-------------------------------*/
    int main()
{
 Tree* T=initTree();
    int n,x,i;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    printf("Enter the tree data\n");

    for(i=0;i<n;i++)
    {
        scanf("%d", &x);
       T->root=  Insert(T->root,x);
    }
    printf("The output is:\n");
    preorder(T->root);
    freenode(T->root);
    free(T);
        return 0;
}
