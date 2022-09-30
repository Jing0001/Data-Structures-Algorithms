#ifndef HW8_FSM_H
#define HW8_FSM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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

bool isDigit(char c);
void appendChar(char* s, char c);
int stateMachine(int inState, int nextChar, char* temp, char* inputLine, int* lineNum_p, int* popInt_p, char* cityStr);

#endif // HW8_HELPER_H
