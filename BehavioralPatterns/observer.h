#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <string>
#include <vector>

//=============================================================================
// Abstract subscriber
//=============================================================================

class Publisher;

class Subscriber
{
protected:
    Publisher *publisher;

public:
    virtual void update() = 0;
    void setPublisher(Publisher *publisher)
    {
        this->publisher = publisher;
    }

    virtual ~Subscriber() {}
};


//=============================================================================
// Subscribers
//=============================================================================

class ConsoleStream : public Subscriber
{
public:
    void update() override;

    ~ConsoleStream() {}
};

//=============================================================================

class FileStream : public Subscriber
{
public:
    void update() override;

    ~FileStream() {}
};

//=============================================================================
// Publisher
//=============================================================================

class Publisher
{
private:
    std::vector<Subscriber*> subs;
    std::string data;

public:
    void addSub(Subscriber *sub)
    {
        subs.push_back(sub);
        sub->setPublisher(this);
    }

    void setData(std::string data)
    {
        this->data = data;
        for (int i = 0; i < subs.size(); i++)
        {
            subs.at(i)->update();
        }
    }

    std::string getData()
    {
        return data;
    }
    
    ~Publisher() {}
};

//=============================================================================
// FileStream and ConsolwStream update methods 
//=============================================================================

void FileStream::update()
{
    std::cout << "Data update recived by file stream" << std::endl;
    std::cout << "New data is: " << publisher->getData() << std::endl;   
}



void ConsoleStream::update()
{
    std::cout << "Data update received by console stream" << std::endl;
    std::cout << "New data is: " << publisher->getData() << std::endl;
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Publisher publisher;

    FileStream *fileStream;
    ConsoleStream *conStream;

    fileStream = new FileStream();
    conStream = new ConsoleStream();

    publisher.addSub(fileStream);
    publisher.addSub(conStream);

    publisher.setData("adfadfadsf");

    delete fileStream;
    delete conStream;

}

#endif //OBSERVER_H
