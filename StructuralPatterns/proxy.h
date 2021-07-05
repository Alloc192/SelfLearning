#ifndef PROXY_H
#define PROXY_H
#include <iostream>
#include <string>

//==============================================================================
// Data storage interface
//==============================================================================

class DataStorage
{
protected:
    std::string data = "";

public:
    virtual std::string readData() = 0;
    virtual void writeData(std::string data) = 0;
    virtual ~DataStorage() {}
};

//==============================================================================
// Data storage class
//==============================================================================

class File : public DataStorage
{
public:
    void writeData(std::string data) override
    {
        this->data += data;
    }

    std::string readData() override
    {
        return data;
    }

    ~File() {}
};

//==============================================================================
// Proxy
//==============================================================================

class AccessLogger : public DataStorage
{
private:
    File *file;

public:
    AccessLogger(File *file)
    {
        this->file = file;
    }

    void writeData(std::string data) override
    {
        std::cout << "Writing some data" << std::endl;
        file->writeData(data);
    }

    std::string readData() override
    {
        std::cout << "Reading data" << std::endl;
        return file->readData();
    }
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    File *file;
    file =  new File();

    DataStorage *dStorage;
    dStorage = new AccessLogger(file);

    dStorage->writeData("Some text 1\n");
    dStorage->writeData("Some text 2\n");
    dStorage->writeData("Some text 3\n");
    std::cout << dStorage->readData() << std::endl;

    delete dStorage;
    delete file;
}



#endif //PROXY_H
