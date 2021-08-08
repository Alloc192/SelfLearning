#ifndef CODE_PARCER_H
#define CODE_PARCER_H
#include <stdio.h>
#include <stdlib.h>

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

char peek(Stack *stack)
{
    int item;
    if(stack->currSize > 0)
    {
        item = stack->itemArr[stack->currSize - 1];
    }
    return item;
}

//=============================================================================
// Brackets validattor based on stack
//=============================================================================

int is_valid(char* str)
{
    Stack *stack;
    stack = (Stack*)malloc(sizeof(Stack));
    stack->itemArr = NULL;
    stack->currSize = 0;
    
    int i = 0;
    while(str[i] != '\0')
    {
        switch (str[i])
        {
        case '(':        
        case '[':
        case '{':
            push(stack, str[i]);
            break;
        
        case ')':
            if(peek(stack) == '(')
            {
                pop(stack);
            }
            break; 

        case ']':
            if(peek(stack) == '[')
            {
                pop(stack);
            }
            break;

        case '}':
            if(peek(stack) == '{')
            {
                pop(stack);
            }
            break;
        }
		i++;
    }
    int result = stack->currSize;
    free(stack->itemArr);
    free(stack);
    return result == 0;
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    char valid_str[]    = "a(b{c[d]e}f)\0"; 
    char invalid_str1[] = "a(b{c[d}e]f)\0";
    char invalid_str2[] = "a(b{c[d]e}f\0";
    printf("%s: \t%d\n", valid_str, is_valid(valid_str));
    printf("%s: \t%d\n", invalid_str1, is_valid(invalid_str1));
    printf("%s: \t%d\n", invalid_str2, is_valid(invalid_str2));
}

#endif // CODE_PARCER_H
