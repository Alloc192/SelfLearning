#ifndef ADAPTER_H
#define ADAPTER_H
#include <iostream>

//==============================================================================
// Client interface
//==============================================================================

class Transport
{
public:
    virtual void turn(double deg) = 0;
    virtual void move(double dist) = 0;
    virtual ~Transport() {}
};

//==============================================================================
// Transport classes
//==============================================================================

class Car : public Transport
{
public:
    void turn(double deg) override
    {
        std::cout << "Car turned " << deg << " degrees" << std::endl;
    }

    void move(double dist) override
    {
        std::cout << "Car moved " << dist << std::endl;
    }

    ~Car() {}
};

//==============================================================================

class Boat
{
public:
    void sail(double dist)
    {
        std::cout << "Ship sailed " << dist << std::endl;
    }

    void turnLeft(double deg)
    {
        std::cout << "Ship turned left " << deg << " degrees" << std::endl;
    }

    void turnRight(double deg)
    {
        std::cout << "Ship turned right " << deg << " degrees" << std::endl;
    }
};

//==============================================================================
// Boat adapter
//==============================================================================

class BoatAdapter : public Transport
{
private:
    Boat *boat;

public:
    BoatAdapter(Boat *boat)
    {
        this->boat = boat;
    }

    void turn(double deg) override
    {
        if(deg > 0)
        {
            boat->turnLeft(deg);
        }
        else
        {
            boat->turnRight(-deg);
        }
    }

    void move(double dist) override
    {
        boat->sail(dist);
    }

    ~BoatAdapter() {};
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    Transport *transport;
    transport = new Car();
    transport->turn(45.0);
    transport->move(25.9);
    transport->turn(-12.5);
    delete transport;

    Boat *boat;
    boat = new Boat();
    transport = new BoatAdapter(boat);
    transport->turn(45.0);
    transport->move(25.9);
    transport->turn(-12.5);
    delete transport;
    delete boat;
}

#endif // ADAPTER_H
