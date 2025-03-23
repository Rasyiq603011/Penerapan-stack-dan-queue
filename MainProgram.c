#include "case.h"

int main() {
    for(;;){
    	Queue operandQueue, operatorQueue;
	    CreateQueue(&operandQueue);
	    CreateQueue(&operatorQueue);
	    
	    infotype operand;
	    char operator;
	    boolean continueCalculation = true;
	    int choice;
	    
	    // Display calculator interface
	    displayInterface();
	    
	    // Get first operand
	    gotoxy(12, 13);
	    setColor(14); // Yellow
	    printf("Enter first operand: ");
	    setColor(15); // Bright white
	    scanf("%d", &operand);
	    EnQueue(&operandQueue, operand);
	    
	    // Update display
	    displayCalculation(operandQueue, operatorQueue);
	    
	    while (continueCalculation) {
	        // Clear menu area
	        int i, j;
	        for (i = 12; i < 69; i++) {
	            for (j = 13; j < 18; j++) {
	                gotoxy(i, j);
	                printf(" ");
	            }
	        }
	        
	        // Menu for operator selection
	        setColor(14); // Yellow
	        gotoxy(20, 12);
	        printf("Choose operator:");
	        
	        setColor(7); // White
	        gotoxy(15, 13);
	        printf("1. Addition");
	        gotoxy(35, 13);
	        printf("2. Subtraction");
	        
	        gotoxy(15, 14);
	        printf("3. Multiplication");
	        gotoxy(35, 14);
	        printf("4. Division");
	        
	        gotoxy(25, 15);
	        printf("5. Equals (=)");
	        
	        gotoxy(25, 17);
	        setColor(14); // Yellow
	        printf("Enter choice: ");
	        setColor(15); // Bright white
	        scanf("%d", &choice);
	        gotoxy(40, 17);
	        
	        switch (choice) {
	            case 1:
	                operator = ADD;
	                break;
	            case 2:
	                operator = SUBTRACT;
	                break;
	            case 3:
	                operator = MULTIPLY;
	                break;
	            case 4:
	                operator = DIVIDE;
	                break;
	            case 5:
	                operator = EQUALS;
	                continueCalculation = false;
	                break;
	            default:
	                setColor(4); // Red
	                printf("Invalid choice. Try again.");
	                Sleep(1000); // Pause to show error
	                continue;
	        }
	        
	        if (operator != EQUALS) {
	            // Add operator to queue
	            EnQueue(&operatorQueue, operator);
	            
	            // Update display
	            displayCalculation(operandQueue, operatorQueue);
	            
	            // Clear input area
	            for (i = 12; i < 69; i++) {
	                for (j = 13; j < 18; j++) {
	                    gotoxy(i, j);
	                    printf(" ");
	                }
	            }
	            
	            // Get next operand
	            gotoxy(12, 13);
	            setColor(14); // Yellow
	            printf("Enter next operand: ");
	            setColor(15); // Bright white
	            scanf("%d", &operand);
	            EnQueue(&operandQueue, operand);
	            
	            // Update display
	            displayCalculation(operandQueue, operatorQueue);
	        }
	    }
	    
	    // Calculate result
	    infotype result = evaluateRPN(operandQueue, operatorQueue);
	    
	    // Clear result area
	    int i;
	    for (i = 12; i < 69; i++) {
	        gotoxy(i, 18);
	        printf(" ");
	    }
	    
	    // Display final result
	    gotoxy(30, 18);
	    setColor(14); // Yellow
	    printf("Result: ");
	    setColor(10); // Light green
	    printf("%d", result);
	    
	    // Display exit message
	    gotoxy(20, 21);
	    setColor(7); // White
	    printf("Operasi lain? (y/n)");
	    if(getchar() == 'y' || getchar() == 'Y'){
	    	break;
		}
	}
    return 0;
}
