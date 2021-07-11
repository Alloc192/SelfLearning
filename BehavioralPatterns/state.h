#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <string>
#include <ctime>
#include <random>

//=============================================================================
// State interface
//=============================================================================

class LineState;

class LineState
{
public:
    virtual LineState* sendData(std::string data) = 0;
    ~LineState() {}
};

//=============================================================================
// Line states
//=============================================================================

class LockedLine;

class UnstableLine;

class FreeLine;

class FreeLine : public LineState
{
public:
    LineState* sendData(std::string data) override;
    ~FreeLine() {}
};

//=============================================================================

class LockedLine : public LineState
{
public:
    LineState* sendData(std::string) override;
    ~LockedLine() {}
};

//=============================================================================

class UnstableLine : public LineState
{
public:
    LineState* sendData(std::string data) override;
    UnstableLine() {}
};

//=============================================================================
// States send data methods
//=============================================================================

LineState* FreeLine::sendData(std::string data)
{
    std::cout << "Line is free, sending data: " << data << std::endl;
    return new LockedLine();
} 

LineState* LockedLine::sendData(std::string data)
{
    std::cout << "Line is locked. Data was not send. Try again later." << std::endl;
    return new UnstableLine();
} 

LineState* UnstableLine::sendData(std::string data)
{
    std::cout << "Unstable line. Data was not send. Try again later." << std::endl;
    std::srand(std::time(nullptr));
    int lineLoad = std::rand() % 100;
    if(lineLoad > 50)
    {
        return new LockedLine();
    }
    return new FreeLine();
} 

//=============================================================================
// Line
//=============================================================================

class Line
{
private:
    LineState *state;

public:
    Line()
    {
        state = new UnstableLine();
    }

    void sendData(std::string data)
    {
        LineState *tmp;
        tmp = state->sendData(data);
        delete state;
        state = tmp;
    }
    
    ~Line() 
    {
        delete state;
    }
};

//=============================================================================
// Run function 
//=============================================================================

void run()
{
    Line line;

    line.sendData("data 1");
    line.sendData("data 2");
    line.sendData("data 3");
    line.sendData("data 4");
    line.sendData("data 5");
    line.sendData("data 6");
    line.sendData("data 7");
    line.sendData("data 8");
    line.sendData("data 9");
    line.sendData("data 10");
}

#endif //STATE_H