// name: Jing Feng
// email: feng.jing1@northeastern.edu

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* function to encrypt the data*/
void encrypt(char text[], int key)
{
    //insert your code here
    for (int i = 0; text[i] != '\0'; i++) {
        char character = text[i];
        char newChar;
        if (character >= 'A' && character <= 'Z') {
            newChar = (character - 'A' + key) % 26 + 'A';
        }
        else if (character >= 'a' && character <= 'z') {
            newChar = (character - 'a' + key) % 26 + 'a';
        }
        else {
            newChar = character;
        }
        text[i] = newChar;
    }
}

/*function to decrypt the data*/
void decrypt(char text[],int key)
{
    
    //insert your code here
    for (int i = 0; text[i] != '\0'; i++) {
        char character = text[i];
        char newChar;
        if (character >= 'A' && character <= 'Z') {
            newChar = (character - 'A' - key + 26) % 26 + 'A';
        }
        else if (character >= 'a' && character <= 'z') {
            newChar = (character - 'a' - key + 26) % 26 + 'a';
        }
        else {
            newChar = character;
        }
        text[i] = newChar;
    }
}


/*----------- Main program---------------*/
int main()
{
    char text[20] ;
    int keyvalue=3;
    /*Input string */
    printf("Enter the message:  ");
    scanf("%s",text);
    printf("text input   = %s\n",text);
    
    /*call function to encrypt the data*/
    encrypt(text,keyvalue);
    printf("Encrypted value = %s\n",text);
    
    /*call function to decrypt the data*/
    decrypt(text,keyvalue);
    printf("Decrypted value = %s\n",text);
    
    return 0;
}
