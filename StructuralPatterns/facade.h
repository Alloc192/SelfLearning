#ifndef FACADE_H
#define FACADE_H
#include <iostream>

//==============================================================================
// Subsystems
//==============================================================================

class Engine
{
public:
    void increaseSpeed()
    {
        std::cout << "Engine speed increased" << std::endl;
    }

    void decreaseSpeed()
    {
        std::cout << "Engine speed decreased" << std::endl;
    }

    ~Engine() {}
};

//==============================================================================

class GearBox
{
private:
    enum gears {R, N, D};
    gears gear = N;

public:

    void shiftToDrive()
    {
        gear = D;
        std::cout << "Gear shifted to drive" << std::endl;
    }

    void shiftToNeutral()
    {
        gear = N;
        std::cout << "Gear shifted to neutral" << std::endl;
    }

    void shiftToReverse()
    {
        gear = R;
        std::cout << "Gear shifted to reverse" << std::endl;
    }

    ~GearBox() {};
};

//==============================================================================

class Brake
{
private:
    bool isPressed = false;

public:
    void activate()
    {
        isPressed = true;
        std::cout << "Brake is pressed" << std::endl;
    }

    void deactivate()
    {
        isPressed = false;
        std::cout << "Brake is released" << std::endl;
    }

    ~Brake() {}
};

//==============================================================================
// Facade
//==============================================================================

class CarFacade
{
private:
    Engine *engine;
    GearBox *gearBox;
    Brake *brake;
   
public:
    CarFacade()
    {
        engine = new Engine();
        gearBox = new GearBox();
        brake = new Brake();
    }

    void driveForward()
    {
        std::cout << "Drive forward" << std::endl;
        brake->activate();
        gearBox->shiftToDrive();
        brake->deactivate();
        engine->increaseSpeed();
        std::cout  << std::endl;
    }

    void stop()
    {
        std::cout << "Stop" << std::endl;
        engine->decreaseSpeed();
        brake->activate();
        gearBox->shiftToNeutral();
        brake->deactivate();
        std::cout  << std::endl;
    }

    void driveBackward()
    {
        std::cout << "Drive forward" << std::endl;
        brake->activate();
        gearBox->shiftToReverse();
        brake->deactivate();
        engine->increaseSpeed();
        std::cout  << std::endl;
    }

    ~CarFacade()
    {
        delete engine;
        delete gearBox;
        delete brake;
    }
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    CarFacade car;
    car.driveForward();
    car.stop();
    car.driveBackward();
}


#endif //FACADE_H
