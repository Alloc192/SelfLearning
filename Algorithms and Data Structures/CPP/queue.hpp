#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

//=============================================================================
// Class Queue
//=============================================================================

template <typename T>
class Queue
{
private:
    int maxSize;
    int currSize;
    T* itemArr;

public:
    Queue(int maxSize)
    {
        this->maxSize = maxSize;
        itemArr = new T[maxSize];
        currSize = 0;
    }
    
    void insert(T item)
    {
        if(currSize < maxSize)
        {
            itemArr[currSize] = item;
            currSize++;
        }
    }

    T remove()
    {
        T item;
        if(currSize > 0)
        {
            item = itemArr[0];
            for(int i = 0; i < currSize - 1; i++)
            {
                itemArr[i] = itemArr[i + 1];
            }
        }
        currSize--;
        return item;
    }

    T peek()
    {
        if(currSize > 0)
        {
            return itemArr[0]; 
        }
    }

    ~Queue()
    {
        delete [] itemArr;
    }
};

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Queue<int> queue(10);
    for(int i = 0; i < 10; i++)
    {
        std::cout << i << std::endl;
        queue.insert(i);
    }
    
    std::cout << queue.peek() << std::endl;

    for(int i = 0; i < 10; i++)
    {
         std::cout << queue.remove() << std::endl; 
    }
}

#endif //QUEUE_H
