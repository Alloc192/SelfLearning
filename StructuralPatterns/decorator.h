#ifndef DECORATOR_H
#define DECORATOR_H
#include <iostream>
#include <string>

//==============================================================================
// Component interface
//==============================================================================

class DataStream
{
public:
    virtual std::string readData() = 0;
    virtual void writeData(std::string data) = 0;
    virtual ~DataStream() {}
};

//==============================================================================
// Component
//==============================================================================

class ConsoleStream : public DataStream
{
public:
    std::string readData() override
    {
        char buffer[300];
        std::cin >> buffer;
        std::string data = buffer;
        return data;
    }

    void writeData(std::string data) override
    {
        std::cout << data << std::endl;
    }

    ~ConsoleStream() {};
};

//==============================================================================
// Coder Decorators
//==============================================================================

class CoderDecorator : public DataStream
{
protected:
    DataStream* stream;

public:
    CoderDecorator(DataStream* stream)
    {
        this->stream = stream;
    }

    virtual std::string readData() = 0;
    virtual void writeData(std::string data) = 0;
    virtual ~CoderDecorator() {}

};

//==============================================================================

class RotCoder : public CoderDecorator
{
private:
    int rotNum;

public:
    RotCoder(DataStream* stream, int rotNum) : CoderDecorator(stream)
    {
        this->rotNum = rotNum;
    };
    std::string readData() override
    {
        std::string data;
        data = stream->readData();
        for(int i = 0; i < data.size(); i++)
        {
            data[i] = (data[i] - 97 + rotNum) % 26 + 97;
        }
        return data;
    }

    void writeData(std::string data) override
    {
        for(int i = 0; i < data.size(); i++)
        {
            data[i] = (data[i] - 97 + 26 - rotNum) % 26 + 97;
        }
        stream->writeData(data);
    }

    ~RotCoder() {}
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    DataStream *stream;
    stream = new ConsoleStream();

    CoderDecorator *decorator;
    decorator = new RotCoder(stream, 13);

    std::string data = decorator->readData();
    std::cout << data << std::endl;

    decorator->writeData(data);

    delete decorator;
    delete stream;
}

#endif //DECORATOR_H
