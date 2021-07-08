#ifndef ITERATOR_H
#define ITERATOR_H
#include <iostream>
#include <string>

//==============================================================================
// Iterable collection interface
//==============================================================================

class Iterator;

class Iterable
{
public:
    virtual Iterator* createIterator() = 0;
    virtual ~Iterable() {}
};

//==============================================================================
// Concrete iterable collection
//==============================================================================

class StrListIterator;

class StringList : public Iterable
{
private:
    std::string data;
    StringList *next = nullptr;

public:
    void setNext(StringList *next)
    {
        this->next = next;
    }

    StringList* getNext()
    {
        return next;
    }

    void setData(std::string data)
    {
        this->data = data;
    }

    std::string getData()
    {
        return data;
    }

    Iterator* createIterator() override;


    ~StringList()
    {
        if(next != nullptr)
        delete next;
    }
};

//==============================================================================
// Iterator interface
//==============================================================================

class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual ~Iterator() {}
};

//==============================================================================
// Concrete iterator
//==============================================================================


class StrListIterator : public Iterator
{
private:
    StringList *head;
    StringList *curr;

public:
    StrListIterator(StringList *head)
    {
        this->head = head;
        this->curr = head;
    }

    bool hasNext() override
    {
        return (curr->getNext() != nullptr);
    }

    StringList* getNext()
    {
        curr = curr->getNext();
        return curr;
    }

    ~StrListIterator() {}
};

//==============================================================================
// StringList::createIterator method
//==============================================================================

Iterator* StringList::createIterator()
{
     return new StrListIterator(this);
}

//==============================================================================
// Run function
//==============================================================================

void run()
{
    StringList *strLst;
    strLst = new StringList();

    StringList *elem = strLst;

    for (int i = 0; i < 10; i++)
    {
        StringList *tmp;
        tmp = new StringList();
        elem->setData("elemeint number " + std::to_string(i));
        elem->setNext(tmp);
        elem = tmp;
    }

    StrListIterator *iterator;
    iterator = dynamic_cast<StrListIterator*>(strLst->createIterator());

    while(iterator->hasNext())
    {
        StringList *tmp;
        tmp = iterator->getNext();
        std::cout << tmp->getData() << std::endl;
    }

    delete iterator;
    delete strLst;
}

#endif //ITERATOR_H
