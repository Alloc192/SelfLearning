#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <iostream>
#include <string>

//==============================================================================
// Products
//==============================================================================

class IBar
{
public:
    virtual void reprBar() = 0;
    virtual ~IBar() {};
};

class IFrame
{
public:
    virtual void reprFrame() = 0;
    virtual ~IFrame() {};
};

//==============================================================================

class MetalBar : public IBar
{
private:
    double length;

public:
    MetalBar(double length);
    void reprBar() override;
    ~MetalBar();
};

MetalBar::MetalBar(double length)
{
    std::cout << "MetalBar constructor called" << std::endl;
    this->length = length;
}

void MetalBar::reprBar()
{
    std::cout << "MetalBar with length " << length << std::endl;
}

MetalBar::~MetalBar()
{
    std::cout << "MetalBar destructor called" << std::endl;
}



class MetalFrame : public IFrame
{
private:
    int width;
    int height;

public:
    MetalFrame(int width, int height);
    void reprFrame() override;
    ~MetalFrame();
};

MetalFrame::MetalFrame(int width, int height)
{
    std::cout << "MetalFrame constructor called" << std::endl;
    this->width = width;
    this->height = height;
}

void MetalFrame::reprFrame()
{
    std::cout << "MetalFrame with width " << width
              << " and height " << height << std::endl;
}

MetalFrame::~MetalFrame()
{
    std::cout << "MetalFrame destructor called" << std::endl;
}

//==============================================================================

class WoodBar : public IBar
{
private:
    double length;
    std::string woodType;

public:
    WoodBar(double length, std::string woodType);
    void reprBar() override;
    ~WoodBar();
};

WoodBar::WoodBar(double length, std::string woodType)
{
    std::cout << "WoodBar constructor called" << std::endl;
    this->length = length;
    this->woodType = woodType;
}

void WoodBar::reprBar()
{
    std::cout << "WoodBar of " << woodType
              << " with length " << length << std::endl;
}

WoodBar::~WoodBar()
{
    std::cout << "WoodBar destructor called" << std::endl;
}



class WoodFrame : public IFrame
{
private:
    int width;
    int height;
    std::string woodType;

public:
    WoodFrame(int width, int height, std::string woodType);
    void reprFrame() override;
    ~WoodFrame();
};

WoodFrame::WoodFrame(int width, int height, std::string woodType)
{
    std::cout << "WoodFrame constructor called" << std::endl;
    this->width = width;
    this->height = height;
    this->woodType = woodType;
}

void WoodFrame::reprFrame()
{
    std::cout << "WoodFrame of " << woodType
              <<" with width " << width
              << " and height " << height << std::endl;
}

WoodFrame::~WoodFrame()
{
    std::cout << "WoodFrame destructor called" << std::endl;
}

//==============================================================================
// Factories
//==============================================================================

class AbstractFactory
{
public:
    virtual IFrame* createFrame() = 0;
    virtual IBar* createBar() = 0;
    virtual ~AbstractFactory() {}
};

//==============================================================================

class MetalFactory : public AbstractFactory
{
public:
    IFrame* createFrame() override;
    IBar* createBar() override;
    ~MetalFactory() {}
};

IFrame* MetalFactory::createFrame()
{
    return new MetalFrame(10, 20);
}

IBar* MetalFactory::createBar()
{
    return new MetalBar(10);
}

//==============================================================================

class WoodFactory : public AbstractFactory
{
public:
    IFrame* createFrame() override;
    IBar* createBar() override;
    ~WoodFactory() {};
};

IFrame* WoodFactory::createFrame()
{
    return new WoodFrame(10, 10, "Pine");
}

IBar* WoodFactory::createBar()
{
    return new WoodBar(10, "Oak");
}

//==============================================================================
// Run function
//==============================================================================

void run()
{
    AbstractFactory *factory;
    IFrame *frame;
    IBar *bar;

    factory = new MetalFactory();
    frame = factory->createFrame();
    bar = factory->createBar();

    frame->reprFrame();
    bar->reprBar();

    delete factory;
    delete frame;
    delete bar;

    factory = new WoodFactory();
    frame = factory->createFrame();
    bar = factory->createBar();

    frame->reprFrame();
    bar->reprBar();

    delete factory;
    delete frame;
    delete bar;
}

#endif // ABSTRACT_FACTORY_H
