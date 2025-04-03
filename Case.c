#include "case.h"

// Function to get console handle
HANDLE Out() {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

// Function to move cursor to specific position
void gotoxy(int x, int y) {
    COORD Point;
    Point.X = x;
    Point.Y = y;
    SetConsoleCursorPosition(Out(), Point);
}

// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(Out(), color);
}

// Function to draw a box
void drawBox(int x1, int y1, int x2, int y2) {
    int i;
    
    // Draw top horizontal line
    gotoxy(x1, y1);
    printf("+");
    for (i = x1 + 1; i < x2; i++) {
        gotoxy(i, y1);
        printf("-");
    }
    gotoxy(x2, y1);
    printf("+");
    
    // Draw vertical lines
    for (i = y1 + 1; i < y2; i++) {
        gotoxy(x1, i);
        printf("|");
        gotoxy(x2, i);
        printf("|");
    }
    
    // Draw bottom horizontal line
    gotoxy(x1, y2);
    printf("+");
    for (i = x1 + 1; i < x2; i++) {
        gotoxy(i, y2);
        printf("-");
    }
    gotoxy(x2, y2);
    printf("+");
}

// Function to display calculator interface
void displayInterface() {
    clearScreen();
    
    // Set console title
    SetConsoleTitle("RPN Calculator");
    
    // Main box
    drawBox(1, 1, 78, 24);
    
    // Title
    setColor(14); // Yellow
    gotoxy(30, 3);
    printf("RPN CALCULATOR");
    
    // Display box
    drawBox(10, 5, 70, 9);
    
    // Menu box
    drawBox(10, 11, 70, 19);
    
    // Reset color
    setColor(7); // White
}

infotype evaluateRPN(Queue operandQueue, Queue operatorQueue) {
    // Check if we have any operands
    if (IsQueueEmpty(operandQueue)) {
        return 0; // No operands
    }
    
    // Count number of operands and operators
    int operandCount = CountQueue(operandQueue);
    int operatorCount = CountQueue(operatorQueue);
    
    // We need at least one operand and one less operator than operands
    if (operandCount == 0 || (operatorCount != operandCount - 1)) {
        return 0; // Invalid expression
    }
    
    // Create stacks to hold operands and operators
    Stack operandStack, operatorStack;
    CreateStack(&operandStack);
    CreateStack(&operatorStack);
    
    infotype temp;
    
    // Process multiply and divide first
    Stack resultOperands, remainingOperators;
    CreateStack(&resultOperands);
    CreateStack(&remainingOperators);

	DeQueue(&operandQueue, &temp);
	StackAdd(&resultOperands, temp);
    
    // Process all operators
    while (!IsQueueEmpty(operatorQueue)) {
        // Get next operator and operand
        infotype op, nextOperand;
        DeQueue(&operatorQueue, &op);
        DeQueue(&operandQueue, &nextOperand);
        
        // Handle multiply and divide immediately
        if (op == MULTIPLY || op == DIVIDE) {
            infotype currentOperand;
            StackDel(&resultOperands, &currentOperand);
            
            if (op == MULTIPLY) {
                StackAdd(&resultOperands, currentOperand * nextOperand);
            } else if (op == DIVIDE) {
                if (nextOperand == 0) {
                    gotoxy(20, 20);
                    setColor(12);
                    printf("Error: Division by zero");
                    setColor(7);
                    Sleep(2000);
                    return 0;
                }
                StackAdd(&resultOperands, currentOperand / nextOperand);
            }
        } else {
            // For add and subtract, store for second pass
            StackAdd(&resultOperands, nextOperand);
            StackAdd(&remainingOperators, op);
        }
    }
    
    // Second pass: handle addition and subtraction
    // Get the first operand as our starting result
    infotype result;
    StackDel(&resultOperands, &result);
    
    // Process remaining operators (add and subtract)
    while (!IsStackEmpty(remainingOperators)) {
        infotype op, nextOperand;
        StackDel(&remainingOperators, &op);
        StackDel(&resultOperands, &nextOperand);
        
        if (op == ADD) {
            result = result + nextOperand;
        } else if (op == SUBTRACT) {
            result = result - nextOperand;
        }
    }
    
    return result;
}

// Function to display the current calculation
void displayCalculation(Queue operandQueue, Queue operatorQueue) {
    // Position and format for display area
    gotoxy(12, 6);
    setColor(11); // Light cyan
    printf("Current calculation: ");
    
    // Clear previous calculation display
    gotoxy(12, 7);
    int i;
    for (i = 0; i < 56; i++) {
        printf(" ");
    }
    
    gotoxy(12, 7);
    setColor(15); // Bright white
    
    // Create temporary queues
    Queue tempOperandQ, tempOperatorQ;
    CreateQueue(&tempOperandQ);
    CreateQueue(&tempOperatorQ);
    
    // Variables for items
    infotype operandItem, operatorItem;
    
    // Copy operand queue to temp queue
    while (!IsQueueEmpty(operandQueue)) {
        DeQueue(&operandQueue, &operandItem);
        EnQueue(&tempOperandQ, operandItem);
    }
    
    // Copy operator queue to temp queue
    while (!IsQueueEmpty(operatorQueue)) {
        DeQueue(&operatorQueue, &operatorItem);
        EnQueue(&tempOperatorQ, operatorItem);
    }
    
    // Create arrays to store values
    int operands[50], operators[50];
    int operandCount = 0, operatorCount = 0;
    
    // Copy values from temp queues to arrays
    while (!IsQueueEmpty(tempOperandQ)) {
        DeQueue(&tempOperandQ, &operandItem);
        operands[operandCount++] = operandItem;
        EnQueue(&operandQueue, operandItem); // Restore original queue
    }
    
    while (!IsQueueEmpty(tempOperatorQ)) {
        DeQueue(&tempOperatorQ, &operatorItem);
        operators[operatorCount++] = operatorItem;
        EnQueue(&operatorQueue, operatorItem); // Restore original queue
    }
    
    // Display calculation
    if (operandCount > 0) {
        printf("%d", operands[0]);
    }
    
    // Display operator-operand pairs
    for (i = 0; i < operatorCount && i + 1 < operandCount; i++) {
        // Display operator with color
        if ((char)operators[i] == '*' || (char)operators[i] == '/') {
            setColor(12); // Light red for high precedence operators
        } else {
            setColor(10); // Light green for low precedence operators
        }
        
        printf(" %c ", (char)operators[i]);
        setColor(15); // Back to bright white
        
        // Display operand
        printf("%d", operands[i + 1]);
    }
    
    setColor(7); // White
}

void clearScreen() {
    system("cls");
}

int getPrecedence(char op) {
    if (op == MULTIPLY || op == DIVIDE)
        return 2;
    else if (op == ADD || op == SUBTRACT)
        return 1;
    else
        return 0;
}
