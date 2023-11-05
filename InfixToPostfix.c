#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char stack[10];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    return stack[top--];
}

int preced(char x) {
    if (x == '(')
        return 0;
    else if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;

}

int main() {
    char array[10];
    printf("Enter infix expression: ");
    scanf("%s", array);


    int i = 0;char j;
    while (array[i] != '\0') {
        if (isalnum(array[i])) {
            printf("%c",array[i]);
        } else if (array[i] == '(') {
            push(array[i]);
        } else if (array[i] == ')') {
            while (j = pop()) {
                    if(j=='(')
                       break;
                    else
                    printf("%c",j);
            }
        }
        else {
            while (top >= 0 && preced(stack[top]) >= preced(array[i])) {
                printf("%c",pop());
            }
            push(array[i]);
        }
        i++;
    }

    while (top >= 0) {
        printf("%c",pop());
    }



    return 0;
}
