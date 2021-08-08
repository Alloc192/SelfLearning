#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>

//=============================================================================
// Stack
//=============================================================================

struct Stack
{
    int *item_arr;
    int curr_size;
};

//=============================================================================

void push(Stack *stack, int value)
{
    stack->item_arr = (int*)realloc(stack->item_arr,
                                    ++stack->curr_size * sizeof(int));
    stack->item_arr[stack->curr_size - 1] = value;
}

//=============================================================================

int pop(Stack *stack)
{
    int item = 0;
    if(stack->curr_size > 0)
    {
        item = stack->item_arr[--stack->curr_size];
        stack->item_arr = (int*)realloc(stack->item_arr,
                                        stack->curr_size * sizeof(int));
    }
    return item;
}

//=============================================================================

int peek(Stack *stack)
{
    int item;
    if(stack->curr_size > 0)
    {
        item = stack->item_arr[stack->curr_size - 1];
    }
    return item;
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Stack *stack;
    stack = (Stack*)malloc(sizeof(Stack));
    stack->item_arr = NULL;
    stack->curr_size = 0;
    for(int i = 0; i < 10; i++)
    {
        printf("Pushing %d to stack\n", i);
        push(stack, i);
    }
    printf("Peeking %d from stack\n", peek(stack));

    for(int i = 0; i < 10; i++)
    {
        printf("Popping %d from stack\n", pop(stack));
    }
    free(stack);
}

#endif //STACK_H
