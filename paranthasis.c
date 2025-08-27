#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValid(char * c) {
    char stack[strlen(c)];
    int top = -1;
    
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '(' || c[i] == '{' || c[i] == '[') {
            stack[++top] = c[i]; // Push opening bracket
        } else {
            if (top == -1 || 
               (c[i] == ')' && stack[top] != '(') || 
               (c[i] == '}' && stack[top] != '{') || 
               (c[i] == ']' && stack[top] != '[')) {
                return false; // Invalid if no match
            }
            top--; // Pop the matching opening bracket
        }
    }
    return top == -1; // Valid if stack is empty
}
