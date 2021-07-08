#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <iostream>
#include <string>


//==============================================================================
// Mediator interface
//==============================================================================

class Mediator
{
public:
    virtual void notify(void *sender) = 0;
    virtual ~Mediator() {}
};

//==============================================================================
// Subsystems
//==============================================================================

enum NetworkState {OFFLINE = 0, ONLINE = 1};

class NetworkSubsystem
{


private:
    NetworkState state;
    Mediator *mediator;
    std::string buffer;

public:
    void setState(NetworkState state)
    {
        this->state = state;
    }

    void setMediator(Mediator *mediator)
    {
        this->mediator = mediator;
    }

    NetworkState getState()
    {
        return state;
    }

    void onRecv()
    {
        buffer = "Data to receive";
        mediator->notify(this);
    }

    std::string readFromBuff()
    {
        return buffer;
    }

    void write(std::string data)
    {
        std::cout << "Sent data: " << data << std::endl;
    }

    ~NetworkSubsystem() {}
};

//==============================================================================

class SendSubsystem
{
private:
    std::string buffer;
    Mediator *mediator;

public:
    void writeToBuff(std::string data)
    {
        buffer = data;
        mediator->notify(this);
    }

    void setMediator(Mediator *mediator)
    {
        this->mediator = mediator;
    }

    std::string readFromBuff()
    {
        return buffer;
    }

    ~SendSubsystem() {}
};

//==============================================================================
// Mediator
//==============================================================================

class ReadSubsystem
{
private:
    std::string buffer;

public:
    void write(std::string data)
    {
        std::cout << "Recieved data: " << data << std::endl;
    }

    ~ReadSubsystem() {}
};

//==============================================================================

class SystemMediator : public Mediator
{
private:
    ReadSubsystem *readSubsys;
    SendSubsystem *sendSubsys;
    NetworkSubsystem *netSubsys;

public:
    SystemMediator(
            ReadSubsystem *readSubsys,
            SendSubsystem *sendSubsys,
            NetworkSubsystem *netSubsys
            )
    {
        this->readSubsys = readSubsys;
        this->sendSubsys = sendSubsys;
        this->netSubsys = netSubsys;
        netSubsys->setMediator(this);
        sendSubsys->setMediator(this);
    }

    void notify(void *sender) override
    {
        if(sender == netSubsys)
        {
            reactOnNet();
        }
        else if(sender == sendSubsys)
        {
            reactOnSend();
        }
    }

    void reactOnNet()
    {
        std::string buffer;
        buffer = netSubsys->readFromBuff();
        readSubsys->write(buffer);
    }

    void reactOnSend()
    {
        if(netSubsys->getState() == NetworkState::ONLINE)
        {
            std::string buffer;
            buffer = sendSubsys->readFromBuff();
            netSubsys->write(buffer);
        }
        else
        {
            std::cout << "Network subsystem is offline, can't send data." <<
                         std::endl;
        }
    }

    ~SystemMediator() {}
};

//==============================================================================
// Run function
//==============================================================================


void run()
{
    ReadSubsystem *readSubsys;
    SendSubsystem *sendSubsys;
    NetworkSubsystem *netSubsys;

    readSubsys = new ReadSubsystem();
    sendSubsys = new SendSubsystem();
    netSubsys = new NetworkSubsystem();

    Mediator *mediator;
    mediator = new SystemMediator(readSubsys, sendSubsys, netSubsys);

    netSubsys->onRecv();

    netSubsys->setState(NetworkState::ONLINE);
    sendSubsys->writeToBuff("Data to send");

    netSubsys->setState(NetworkState::OFFLINE);
    sendSubsys->writeToBuff("Data to send");

    delete mediator;
    delete readSubsys;
    delete sendSubsys;
    delete netSubsys;
}

#endif //MEDIATOR_H
