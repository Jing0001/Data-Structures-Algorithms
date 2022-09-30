// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    if(n < 2){
        for(int i = 0; i < n; i++){
            printf("%c", arr[i]);
        }
        return n;
    }
    int i = 1;
    int j;
    int count=1;//counter
    int index=0;//to store the result
    char r[10];
    char curr = arr[0];
    while(i <= n){
        if(arr[i] != curr) {
            res[index++] = curr;
            if(count != 1){
                sprintf(r, "%d", count);
                for(j = 0; j < strlen(r); j++) {  
                    res[index++] = r[j];
                }
            }
            count = 1;
        }
        else{
            count++;
        }
        curr = arr[i++];
    }
    count = 0;
    for(i = 0; i < index; i++){
        printf("%c", res[i]);
        count += 1;
    }
    printf("\n");
    return count;
    
}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("length of the compressed string:%d\n",r);
    return 0;
}
