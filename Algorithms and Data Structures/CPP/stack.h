#ifndef STACK_H
#define STACK_H
#include <iostream>

//=============================================================================
// Class Stack
//=============================================================================

template <typename T>
class Stack
{
private:
    T *itemArr;
    int maxSize;
    int currTop;

public:
    Stack(int maxSize)
    {
        this->maxSize = maxSize;
        itemArr = new T[maxSize];
        currTop = -1;
    }
    
    void push(T item)
    {
        if(currTop < maxSize)
        {
            currTop += 1;
            itemArr[currTop] = item;
        }
    }

    T pop()
    {
        T item;
        if(currTop >= 0)
        {
            item = itemArr[currTop];
            currTop -= 1;
        }
        return item;
    }

    T peek()
    {
        T item;
        if(currTop >= 0)
        {
            item = itemArr[currTop];
        }
        return item;
    }

    ~Stack()
    {
        delete [] itemArr;
    }
};

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Stack<int> stack(10);
    for(int i = 0; i < 10; i++)
    {
        std::cout << i << std::endl;
        stack.push(i);
    }
    
    std::cout << stack.peek() << std::endl;
    for(int i = 0; i < 10; i++)
    {
         std::cout << stack.pop() << std::endl; 
    }
}

#endif //STACK_H
