#ifndef STRATEGY_H
#define STRATEGY_H
#include <iostream>
#include <string>

//=============================================================================
// Strategy interface
//=============================================================================

class Transmiter
{
public:
    virtual void send(std::string data) = 0;
    virtual std::string recv() = 0;
    ~Transmiter() {}
};

//=============================================================================
// Strategies
//=============================================================================

class Radio : public Transmiter
{
public:
    void send(std::string data) override
    {
        std::cout << "Sending data to radio channel. Data: " 
                  << data << std::endl;
    }

    std::string recv() override
    {
        std::string data = "Some data";
        std::cout << "Receiving data from radio channel." << std::endl;
        return data;
    }
    ~Radio() {}
};

//=============================================================================

class Cord : public Transmiter
{
public:
    void send(std::string data) override
    {
        std::cout << "Sending data to cord channel. Data: " 
                  << data << std::endl;
    }

    std::string recv() override
    {
        std::string data = "Some data";
        std::cout << "Receiving data from cord channel." << std::endl;
        return data;
    }
    ~Cord() {}
};

//=============================================================================
// Communicator
//=============================================================================

class Communicator
{
private:
    Transmiter *transmiter;
    
public:
    Communicator(Transmiter *transmiter)
    {
        this->transmiter = transmiter;
    }

    void ping()
    {
        transmiter->send("PING");
        std::cout << transmiter->recv() << std::endl;
    }

    ~Communicator()
    {
        delete transmiter;
    }
};


//=============================================================================
// Run function
//=============================================================================

void run()
{
    Communicator *communicator;
    communicator = new Communicator(new Radio());
    communicator->ping();

    delete communicator;

    communicator = new Communicator(new Cord());
    communicator->ping();

    delete communicator;    
}

#endif //STRATEGY_H