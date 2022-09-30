// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include<stdio.h>
#define MAXN 50       /* largest number of books */
#define MAXK 10        /* largest number of dividers */
#define MAXINT 100000  /* infinity */

/*function to find the maximum of two numbers*/
int max(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}

/* function to calculate the sum of an array*/
int sum(int arr[], int from, int to)
{
    int total = 0;
    for (int i = from; i <= to; i++)
        total += arr[i];
    return total;
}
/* function to print the books with partition*/
void print_books(int s[], int start, int end)
{
    int i;            /* counter */
    
    printf("\n{");
    for (i=start; i<=end; i++)
    printf(" %d ",s[i]);
    printf("}\n");
}

/* function to print the DP table */
void print_matrix(int m[MAXN][MAXK], int n, int k)
{
    int i,j;        /* counters */

    printf("DP Table\n");
    printf("\n");
    for (i=1; i<=n; i++) {
        for (j=1; j<=k; j++)
            printf(" %d ",m[i][j]);
            printf("\n");
    }
}

/* Recursive function to reconstruct the partition to print the books*/
void reconstruct_partition(int s[],int d[MAXN][MAXK], int n, int k)
{
    if (k==1)  //base case
        print_books(s,1,n);
    else {
        reconstruct_partition(s,d,d[n][k],k-1);
        print_books(s,d[n][k]+1,n);
    }
}

/* Function to create DP table for n books and k partitions*/
void partition(int s[], int n, int k)
{
    int p[MAXN];                /* prefix sums array */
    int m[MAXN][MAXK];            /* DP table for values */
    int d[MAXN][MAXK];            /* DP table for dividers */
    int cost;                /* track the minimum cost*/
    int i,j,x;                /* counters */

    
    
    /*Insert your code here*/
    p[0] = 0;
    for(i = 1; i <= n; i++){
        p[i] = p[i - 1] + s[i];
    }
    for(j = 1; j <= n; j++){
        m[j][1] = p[j];
    }
    for(x = 1; x <= k; x++){
        m[1][x] = m[1][1];
    }


    
    
/* 2 to k partitions*/
for (i=2; i<=n; i++)
    
for (j=2; j<=k; j++)
{
    m[i][j]=MAXINT; /*initialize infinity*/
            
    for (x=1; x<=i-1; x++)
    {
    cost = max(m[x][j-1],p[i]-p[x]);
       //cost = max(m[x][j-1],sum(s,x+1,i));
        if(m[i][j]>cost)
            {
            m[i][j]=cost;
/* position of dividers is stored in matrix d*/
            d[i][j] = x;
            }
        }
}
    print_matrix(m,n,k);
    printf("Partition of the books are:\n");
    reconstruct_partition(s,d,n,k);        /* print book partition */
}


/*-------------- Main program--------*/
int main()
{
    int s[MAXN];       /* book thicknesses to partition */
    int n,i;           /* how many books? */
    int k;             /* how many partitions? */
    n=9;               /* total 9 books*/
    k=3;               /* 3 partitions*/
    
    printf("Enter the thickness of each books\n");
    for (i=1; i<=n; i++)
    {
    scanf("%d",&s[i]);
    }
    printf("\n");
    partition(s,n,k);
    return 0;
}

 
 
