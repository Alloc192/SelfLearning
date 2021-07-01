#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>

//==============================================================================
// Parts
//==============================================================================

struct Frame
{
    double weight;
    void repr()
    {
        std::cout << "Frame with weight " << weight  << std::endl;
    }
};

//==============================================================================

struct Sprocket
{
    int teethNum;
    void repr()
    {
        std::cout << "Sprocket with " << teethNum << " teeth" << std::endl;
    }
};

//==============================================================================

struct Wheel
{
    double diameter;
    void repr()
    {
        std::cout << "Wheel with diameter " << diameter <<  std::endl;
    }
};

//==============================================================================

struct Pedals
{
    double armLength;
    void repr()
    {
        std::cout << "Wheel with arm length " << armLength <<  std::endl;
    }
};

//==============================================================================

struct Engine
{
    double power;
    int cilinderCount;
    double volume;
    char configuration;

    void repr()
    {
        std::cout << configuration << cilinderCount <<
                     "engine, HP: " << power <<
                     ", Vol: " << volume << std::endl;
    }
};

//==============================================================================
// Building Objects
//==============================================================================

class Bicycle
{
private:
    Frame frame;
    Sprocket drivingGear;
    Sprocket drivenGear;
    Wheel frontWheel;
    Wheel rearWheel;
    Pedals pedals;

public:
    Bicycle(Frame frame)
    {
        std::cout << "Bicycle constructor called" << std::endl;
        this->frame = frame;
    }

    void setGears(Sprocket drivingGear, Sprocket drivenGear)
    {
        this->drivingGear = drivingGear;
        this->drivenGear = drivenGear;
    }

    void setWheels(Wheel frontWheel, Wheel rearWheel)
    {
        this->frontWheel = frontWheel;
        this->rearWheel = rearWheel;
    }

    void setPedals(Pedals pedals)
    {
        this->pedals = pedals;
    }

    void repr()
    {
        std::cout << "Bicycle with params:" << std::endl;

        frame.repr();
        std::cout << "Driving gear: ";
        drivingGear.repr();
        std::cout << "Driven gear: ";
        drivenGear.repr();
        std::cout << "Front wheel: ";
        frontWheel.repr();
        std::cout << "Rear wheel: ";
        rearWheel.repr();
        std::cout << "Propulsor: ";
        pedals.repr();
    }
};

//==============================================================================

class Motorbike
{
private:
    Frame frame;
    Sprocket drivingGear;
    Sprocket drivenGear;
    Wheel frontWheel;
    Wheel rearWheel;
    Engine engine;

public:
    Motorbike(Frame frame)
    {
        std::cout << "Motorbike constructor called" << std::endl;
        this->frame = frame;
    }

    void setGears(Sprocket drivingGear, Sprocket drivenGear)
    {
        this->drivingGear = drivingGear;
        this->drivenGear = drivenGear;
    }

    void setWheels(Wheel frontWheel, Wheel rearWheel)
    {
        this->frontWheel = frontWheel;
        this->rearWheel = rearWheel;
    }

    void setEngine(Engine engine)
    {
        this->engine = engine;
    }

    void repr()
    {
        std::cout << "Motorbike with params:" << std::endl;

        frame.repr();
        std::cout << "Driving gear: ";
        drivingGear.repr();
        std::cout << "Driven gear: ";
        drivenGear.repr();
        std::cout << "Front wheel: ";
        frontWheel.repr();
        std::cout << "Rear wheel: ";
        rearWheel.repr();
        std::cout << "Propulsor: ";
        engine.repr();
    }
};

//==============================================================================
// Builders
//==============================================================================

class Builder
{
public:
    virtual void buildGears() = 0;
    virtual void buildWheels() = 0;
    virtual void buildPropulsor() = 0;
    virtual ~Builder() {};
};

//==============================================================================

class BicycleBuilder : public Builder
{
private:
    Bicycle *bicycle;

public:
    BicycleBuilder()
    {
        Frame frame;
        frame.weight = 12.5;
        bicycle = new Bicycle(frame);
    }

    void buildGears() override
    {
        Sprocket drivingGear;
        Sprocket drivenGear;
        drivingGear.teethNum = 28;
        drivenGear.teethNum = 12;
        bicycle->setGears(drivingGear, drivenGear);
    }

    void buildWheels() override
    {
        Wheel frontWheel;
        Wheel rearWheel;
        frontWheel.diameter = 22.8;
        rearWheel.diameter = 22.8;
        bicycle->setWheels(frontWheel, rearWheel);
    }

    void buildPropulsor() override
    {
        Pedals pedals;
        pedals.armLength = 18.0;
        bicycle->setPedals(pedals);
    }

    Bicycle* getResult()
    {
        return bicycle;
    }
    ~BicycleBuilder() {};
};

//==============================================================================

class MotorbikeBuilder : public Builder
{
private:
    Motorbike *motorbike;

public:
    MotorbikeBuilder()
    {
        Frame frame;
        frame.weight = 25.0;
        motorbike = new Motorbike(frame);
    }

    void buildGears() override
    {
        Sprocket drivingGear;
        Sprocket drivenGear;
        drivingGear.teethNum = 14;
        drivenGear.teethNum = 32;
        motorbike->setGears(drivingGear, drivenGear);
    }

    void buildWheels() override
    {
        Wheel frontWheel;
        Wheel rearWheel;
        frontWheel.diameter = 18.5;
        rearWheel.diameter = 16.5;
        motorbike->setWheels(frontWheel, rearWheel);
    }

    void buildPropulsor() override
    {
        Engine engine;
        engine.power = 23;
        engine.cilinderCount = 2;
        engine.volume = 1000;
        engine.configuration = 'V';
        motorbike->setEngine(engine);
    }

    Motorbike* getResult()
    {
        return motorbike;
    }

    virtual ~MotorbikeBuilder() {};
};

//==============================================================================
// Director
//==============================================================================

class Director
{
private:
    Builder *builder;

public:
    Director(Builder *builder)
    {
        this->builder = builder;
    }

    void build()
    {
        builder->buildGears();
        builder->buildWheels();
        builder->buildPropulsor();
    }

    ~Director() {};
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    MotorbikeBuilder motoBuilder;
    Motorbike *motorbike;
    Director *director;

    director = new Director(&motoBuilder);
    director->build();
    delete director;
    motorbike = motoBuilder.getResult();
    motorbike->repr();
    delete motorbike;

    BicycleBuilder bicycleBuilder;
    Bicycle *bicycle;

    director = new Director(&bicycleBuilder);
    director->build();
    delete director;
    bicycle = bicycleBuilder.getResult();
    bicycle->repr();
    delete bicycle;
}

#endif // BUILDER_H
