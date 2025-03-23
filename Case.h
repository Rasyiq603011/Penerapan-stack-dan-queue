#ifndef CASE_H
#define CASE_H

#include "Queue.h"
#include "stack.h"
#include <windows.h>

// Constants for operators
#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define EQUALS '='

// Function to move cursor to specific position
void gotoxy(int x, int y);

// Function to get console handle
HANDLE Out();

// Function to set text color
void setColor(int color);

// Function to draw a box
void drawBox(int x1, int y1, int x2, int y2);

// Function to display calculator interface
void displayInterface();

// Function to evaluate the expression using RPN
infotype evaluateRPN(Queue operandQueue, Queue operatorQueue);

// Function to display the current calculation
void displayCalculation(Queue operandQueue, Queue operatorQueue);

// Function to clear the screen
void clearScreen();

// Function to get precedence of an operator
int getPrecedence(char op);

#endif
