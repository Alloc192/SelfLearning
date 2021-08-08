#ifndef DEQUEUE_H
#define DEQUEUE_H
#include <iostream>

//=============================================================================
// Class Deque - Double Ended Queue
//=============================================================================

template<typename T>
class Deque
{
private:
    int maxSize;
    int currSize;
    T* itemArr;

public:
    Deque(int maxSize)
    {
        this->maxSize = maxSize;
        itemArr = new T[maxSize];
        currSize = 0;
    }

    void insertRight(T item)
    {
        if(currSize < maxSize)
        {
            itemArr[currSize] = item;
            currSize++;
        }
    }

    void insertLeft(T item)
    {
        if(currSize < maxSize)
        {
            currSize++;
            for(int i = currSize; i > 0; i--)
            {
                itemArr[i] = itemArr[i - 1];
            }
            itemArr[0] = item;

        }
    }

    T removeRight()
    {
        T item;
        if(currSize < maxSize)
        {
            item = itemArr[currSize];
            currSize--;
        }
        return item;
    }

    T removeLeft()
    {
        T item;
        if(currSize > 0)
        {
            item = itemArr[0];
            for(int i = 0; i < currSize - 1; i++)
            {
                itemArr[i] = itemArr[i + 1];
            }
            currSize--;
        }
        return item;
    }

    ~Deque()
    {
        delete [] itemArr;
    }
};

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Deque<int> deque(10);
    for(int i = 0; i < 5; i++)
    {
        deque.insertLeft(i);
    }
    for(int i = 5; i < 10; i++)
    {
        deque.insertRight(i);
    }
    for(int i = 0; i < 10; i++)
    {
        std::cout << deque.removeLeft() << std::endl;
    }
}

#endif // DEQUEUE_H
