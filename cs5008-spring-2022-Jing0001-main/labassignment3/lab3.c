//Jing Feng
//feng.jing1@northeastern.edu

#include <stdio.h>
#define MAX 8
int main()
{
    int arr[MAX] = {80,35,56,45,10,90,12,67};
    int i,j,temp;
    
    //insert your code here
    for (i = 1; i < MAX; i++) {
        temp = arr[i];
        j = i - 1;
        while (arr[j] > temp && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
    printf("Sorted list in ascending order:\n");
    for (i = 0; i < MAX; i++) {
        printf("%d\n", arr[i]);
    }

    
    
    
    
    
    
    return 0;
}
