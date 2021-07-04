#ifndef BRIDGE_H
#define BRIDGE_H
#include <iostream>

//==============================================================================
// Engines
//==============================================================================

class Engine
{
public:
    virtual void repr() = 0;
    virtual ~Engine()
    {
        std::cout << "Engine destructor called" << std::endl;
    }
};

//==============================================================================

class GasEngine : public Engine
{
public:
    void repr() override
    {
        std::cout << "Gas engine" << std::endl;
    }

    ~GasEngine()
    {
        std::cout << "Gas engine destructor called" << std::endl;
    }
};

//==============================================================================

class ElectricEngine : public Engine
{
public:
    void repr() override
    {
        std::cout << "Electric engine" << std::endl;
    }

    ~ElectricEngine()
    {
        std::cout << "Electric engine destructor called" << std::endl;
    }
};

//==============================================================================
// Transport
//==============================================================================

class Transport
{
protected:
    Engine *engine;

public:
    virtual void repr() = 0;
    virtual ~Transport()
    {
        std::cout << "Transport destructor called" << std::endl;
        delete engine;
    }
};

//==============================================================================

class Car : public Transport
{
public:
    Car(Engine *engine)
    {
        this->engine = engine;
    }

    void repr() override
    {
        std::cout << "Car with engine: ";
        engine->repr();
    }

    ~Car()
    {
        std::cout << "Car destructor called" << std::endl;
    }
};

//==============================================================================

class Motorbike : public Transport
{
public:
    Motorbike(Engine *engine)
    {
        this->engine = engine;
    }

    void repr() override
    {
        std::cout << "Motorbike with engine: ";
        engine->repr();
    }

    ~Motorbike()
    {
        std::cout << "Motorbike destructor called" << std::endl;
    }
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    Transport *transport;
    transport = new Car(new GasEngine());
    transport->repr();
    delete transport;
    std::cout << std::endl;

    transport = new Car(new ElectricEngine());
    transport->repr();
    delete transport;
    std::cout << std::endl;

    transport = new Motorbike(new GasEngine());
    transport->repr();
    delete transport;
    std::cout << std::endl;

    transport = new Motorbike(new ElectricEngine());
    transport->repr();
    delete transport;
}








#endif // BRIDGE_H
