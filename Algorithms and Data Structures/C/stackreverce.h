#ifndef STACK_REVERSE_H
#define STACK_REVERSE_H
#include <stdlib.h>
#include <stdio.h>

//=============================================================================
// Stack
//=============================================================================

struct Stack
{
    char *itemArr;
    int currSize;
};

//=============================================================================

void push(Stack *stack, char value)
{
    stack->itemArr = (char*)realloc(stack->itemArr,
                                    ++stack->currSize * sizeof(char));
    stack->itemArr[stack->currSize - 1] = value;
}

//=============================================================================

char pop(Stack *stack)
{
    int item = 0;
    if(stack->currSize > 0)
    {
        item = stack->itemArr[--stack->currSize];
        stack->itemArr = (char*)realloc(stack->itemArr,
                                        stack->currSize * sizeof(char));
    }
    return item;
}

//=============================================================================
// String reverse using stack
//=============================================================================

void strReverse(char* str)
{
    Stack *stack;
    stack = (Stack*)malloc(sizeof(Stack));
    stack->itemArr = NULL;
    stack->currSize = 0;
    int i = 0;

    while(str[i] != '\0')
    {
        push(stack, str[i++]);
    }
    
    i = 0;
    while(str[i] != '\0')
    {
        str[i++] = pop(stack);
    }
    free(stack);
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    char str[] = "string for reverse\0";
    printf("Before reverse: %s\n", str);
	strReverse(str);
    printf("After reverse:  %s\n", str);
    
}

#endif // STACK_REVERSE_H
