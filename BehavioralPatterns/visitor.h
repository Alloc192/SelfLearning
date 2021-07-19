#ifndef TEMPLATE_METHOD_H
#define TEMPLATE_METHOD_H
#include <iostream>

//=============================================================================
// Element interface
//=============================================================================

class Visitor;

class Element
{
public:
    virtual void acceptVisitor(Visitor *visitor) = 0;
    virtual ~Element() {}
};

//=============================================================================
// Concrete elements
//=============================================================================

class Coord3D : public Element
{
private:
    double x;
    double y;
    double z;

public:
    Coord3D(double x = 0,double y = 0, double z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    double getZ()
    {
        return z;
    }

    void acceptVisitor(Visitor *visitor) override;

    ~Coord3D() {}
};

//=============================================================================

class Coord2D : public Element
{
private:
    double x;
    double y;

public:
    Coord2D(double x = 0,double y = 0)
    {
        this->x = x;
        this->y = y;
    }

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    void acceptVisitor(Visitor *visitor) override;

    ~Coord2D() {}
};

//=============================================================================
// Visitor interface
//=============================================================================

class Visitor
{
public:
    virtual void visit(Coord2D *coord2D) = 0;
    virtual void visit(Coord3D *coord2D) = 0;
    virtual ~Visitor() {}
};

//=============================================================================
// Concrete visitor interface
//=============================================================================

class ConsoleLogVisitor : public Visitor
{
public:
    void visit(Coord2D *coord2D) override
    {
        std::cout << "x = " << coord2D->getX() <<
                     "; y = " << coord2D->getY() <<
                     ";" << std::endl;
    }

    void visit(Coord3D *coord3D) override
    {
        std::cout << "x = " << coord3D->getX() <<
                     "; y = " << coord3D->getY() <<
                     "; z = " << coord3D->getZ() <<
                     ";" << std::endl;
    }

    ~ConsoleLogVisitor() {}
};

//=============================================================================
// ConcreteElements acceptVisitor methods
//=============================================================================

void Coord2D::acceptVisitor(Visitor *visitor)
{
    visitor->visit(this);
}

//=============================================================================

void Coord3D::acceptVisitor(Visitor *visitor)
{
    visitor->visit(this);
}

//=============================================================================
// Run function
//=============================================================================

void run()
{
    Coord3D coord3D(1.0, 2.0, 3.0);
    Coord2D coord2D(4.0, 5.0);

    Visitor *visitor;
    visitor = new ConsoleLogVisitor();

    coord3D.acceptVisitor(visitor);
    coord2D.acceptVisitor(visitor);

    delete visitor;
}

#endif //TEMPLATE_METHOD_H
