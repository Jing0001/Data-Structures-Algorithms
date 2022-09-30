// name: Jing Feng
// email: feng.jing1@northeastern.edu

// format of document is a bunch of data lines beginning with an integer (rank which we ignore)
// then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas and covert to int
// then a lot of entries that are ignored


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// ***** helper functions *****

// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
  char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}


// *** FINITE STATE MACHINE ***

// advance the FSM one state based on the next character of input in the line
// inState is the old state of the machine...function returns the new state
// nextChar is the index of the next character of input in inputLine
// temp is working memory used to build up substrings one character at a time
// output of the parsed linenum an population are returned by reference in lineNum_p and popInt_p
// output of the parsed geographic name is in cityStr

int stateMachine(int inState, int nextChar, char* temp, char* inputLine, int* lineNum_p, int* popInt_p, char* cityStr) {
    
    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //

  int state = inState;
  
  switch (state) {
  case STARTSTATE:
    // look for a digit to confirm a valid line
    if (isDigit(inputLine[nextChar])) {
      state = S1;
      appendChar(temp, inputLine[nextChar]);
    } else {
      state = ERRORSTATE;
    }  
    break;
         
  case S1:
    // accept digits to build up line number (city rank), terminated by comma
    if (isDigit(inputLine[nextChar])) {
      state = S1;
      appendChar(temp, inputLine[nextChar]);
    } else if (inputLine[nextChar] == ',') {
      state = S2;
      // line number is complete - convert it to an int and store in destination
      sscanf(temp,"%d", lineNum_p); // sscanf returns lineNum by reference
      strcpy(temp, "");             // temp = ""
    } else {
      state = ERRORSTATE;
    } 
    break;
         
  case S2:
    // looking for a double quote
    if (inputLine[nextChar] == '\"') {
      state = S3;
    } else {
      state = ERRORSTATE;
    }
    break;
         
  case S3:
    // accept anything until you find a double quote
    // for city name
    if (inputLine[nextChar] == '\"') {
      state = S4;
      // city name is complete - copy it to destination
      strcpy(cityStr, temp);
      strcpy(temp, "");
    } else {
      // still building up the city name
      state = S3;
      appendChar(temp,inputLine[nextChar]);
    }
    break;
         
  case S4:

    // *** YOUR CODE GOES HERE ***
    if (inputLine[nextChar] == ',') {
      state = S5;
    } else {
      state = ERRORSTATE;
    }
    break;
         
  case S5:

    // *** YOUR CODE GOES HERE ***
    if (inputLine[nextChar] == '\"') {
      state = S6;
    } else {
      state = ERRORSTATE;
    }
    break;
         
  case S6:

    // *** YOUR CODE GOES HERE ***
    if (isDigit(inputLine[nextChar])) {
      state = S6;
      appendChar(temp, inputLine[nextChar]);
    } else if (inputLine[nextChar] == ',') {
      state = S6;
    } else if (inputLine[nextChar] == '\"') {
      sscanf(temp,"%d", popInt_p);
      strcpy(temp, ""); 
      state = ACCEPTSTATE;
    }
    break;
         
  case ACCEPTSTATE:
    // nothing to do - we are done!
    break;
         
  default:
    state = ERRORSTATE;
    break;
  } // end switch
  return state;
}



int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
  
 
  FILE* fp;
  fp = fopen("pop.csv","r");

  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

    while (feof(fp) == 0){

      nextChar = 0;
      state = STARTSTATE; 
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
	// if no input string then go to ERRORSTATE
	state = ERRORSTATE;
      } 

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {

	state = stateMachine(state, nextChar, temp, inputLine, &lineNum, &popInt, cityStr);

	// advance input
	nextChar++;
	
      }  

      // process the line - print out raw line and the parsed fields
      printf("> %.60s\n", inputLine);
      printf("[%.30s]: %d\n", cityStr, popInt);

      // get next line
      fgets(inputLine, MAXSTRING, fp);
      
    } // end while file input loop
    

    fclose(fp);
  
  } else {
    printf("File not found!\n");
  }
  
  return 0;
}
