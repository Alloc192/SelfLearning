#ifndef PROTOTYPE_H
#define PROTOTYPE_H
#include <iostream>
#include <array>

//==============================================================================
// Prototype
//==============================================================================

class ObjectPrototype;

class ObjectPrototype
{
public:
    virtual ObjectPrototype* clone() = 0;
    virtual ~ObjectPrototype() {}
};

//==============================================================================

class PhysicalObject : public ObjectPrototype
{
private:
    double x;
    double y;
    double z;
    std::array<double, 3> velocityVector;

public:
    PhysicalObject(int x, int y, int z, std::array<double, 3> velocityVector)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->velocityVector = velocityVector;
    }
    PhysicalObject()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        velocityVector = {0.0,0.0,0.0};
    }

    void updatePos()
    {
        x += velocityVector.at(0);
        y += velocityVector.at(1);
        z += velocityVector.at(2);
    }

    ObjectPrototype* clone() override
    {
        PhysicalObject *tmp;
        tmp = new PhysicalObject;
        tmp->x = x;
        tmp->y = y;
        tmp->z = z;
        tmp->velocityVector = velocityVector;
        return dynamic_cast<ObjectPrototype*>(tmp);
    }

    void repr()
    {
        std::cout << "x: " << x
                  << "\ty: " << y
                  << "\tz: " << z
                  << "\tVx: " << velocityVector.at(0)
                  << "\tVy: " << velocityVector.at(1)
                  << "\tVz: " << velocityVector.at(2)
                  << std::endl;
    }

    ~PhysicalObject() {}
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    const int traceLen = 10;
    std::array<PhysicalObject*, traceLen> trace;

    std::array<double, 3> initVelVec = {0.5, 1.0, 1.5};

    PhysicalObject *phyObj;
    phyObj = new PhysicalObject(0.0, 0.0, 0.0, initVelVec);

    for(int i = 0; i < traceLen; i++)
    {
        trace.at(i) = dynamic_cast<PhysicalObject*>(phyObj->clone());
        phyObj->updatePos();
    }

    for (PhysicalObject *traceElem : trace)
    {
        traceElem->repr();
    }

    for (PhysicalObject *traceElem : trace)
    {
        delete traceElem;
    }
    delete phyObj;
}



#endif // PROTOTYPE_H
