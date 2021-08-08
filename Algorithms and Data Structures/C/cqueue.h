#if !defined(C_QUEUE_H)
#define C_QUEUE_H
#include <stdlib.h>
#include <stdio.h>

//=============================================================================
// Queue
//=============================================================================

struct Queue
{
    int curr_size;
    int* item_arr;
};

//=============================================================================

void insert(Queue *queue, int value)
{
    queue->curr_size++;
    queue->item_arr = (int*)realloc(queue->item_arr,
                                    queue->curr_size * sizeof(int));
    queue->item_arr[queue->curr_size - 1] = value;
}

//=============================================================================

int remove(Queue *queue)
{
    int item;
    if(queue->curr_size > 0)
    {
        item = queue->item_arr[0];
        queue->curr_size--;
        for(int i  = 0; i < queue->curr_size; i++)
        {
            queue->item_arr[i] = queue->item_arr[i + 1];
        }
        queue->item_arr = (int*)realloc(queue->item_arr,
                                        queue->curr_size * sizeof(int));
    }
    return item;
}

//=============================================================================

int peek(Queue *queue)
{
    if(queue->curr_size > 0)
    {
        return queue->item_arr[0];
    }
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Queue *queue;
    queue = (Queue*)malloc(sizeof(Queue));
    queue->curr_size = 0;
    queue->item_arr = NULL;

    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", i);
        insert(queue, i);
    }
    printf("%d\n", peek(queue));
    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", remove(queue));
    }  
    free(queue);
}

#endif // C_QUEUE_H
