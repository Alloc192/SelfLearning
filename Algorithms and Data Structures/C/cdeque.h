#if !defined(DEQUE_H)
#define DEQUE_H
#include <stdlib.h>
#include <stdio.h>

//=============================================================================
// Deque - Double Ended Queue
//=============================================================================

struct Deque
{
    int *item_arr;
    int curr_size;
};

//=============================================================================

void insert_right(Deque *deque, int value)
{
    deque->curr_size++;
    deque->item_arr = (int*)realloc(deque->item_arr,
                                    deque->curr_size * sizeof(int));
    deque->item_arr[deque->curr_size - 1] = value;
}

//=============================================================================

void insert_left(Deque *deque, int value)
{
    deque->curr_size++;
    deque->item_arr = (int*)realloc(deque->item_arr,
                                    deque->curr_size * sizeof(int));
    for(int i = deque->curr_size - 1; i > 0; i--)
    {
        deque->item_arr[i] = deque->item_arr[i - 1];
    }
    deque->item_arr[0] = value;
}

//=============================================================================

int remove_right(Deque *deque)
{
    int item;
    if(deque->curr_size > 0)
    {
        deque->curr_size--;
        item = deque->item_arr[deque->curr_size];
        deque->item_arr = (int*)realloc(deque->item_arr,
                                        deque->curr_size * sizeof(int));
    }
    return item;
}

//=============================================================================

int remove_left(Deque *deque)
{
    int item;
    if(deque->curr_size > 0)
    {
        deque->curr_size--;
        item = deque->item_arr[0];
        for(int i = 0; i < deque->curr_size; i++)
        {
            deque->item_arr[i] = deque->item_arr[i + 1];
        }
        deque->item_arr = (int*)realloc(deque->item_arr,
                                        deque->curr_size * sizeof(int));
    }
    return item;
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Deque *deque;
    deque = (Deque*)malloc(sizeof(Deque));
    deque->curr_size = 0;
    deque->item_arr = NULL;

    for(int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
        insert_right(deque, i);
    }
    for(int i = 5; i < 10; i++)
    {
        printf("%d\n", i);
        insert_left(deque, i);
    }
    printf("\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", remove_left(deque));
    }
    free(deque);
}

#endif // DEQUE_H
