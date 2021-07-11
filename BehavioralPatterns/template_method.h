#ifndef TEMPLATE_METHOD_H
#define TEMPLATE_METHOD_H
#include <iostream>
#include <string>

//=============================================================================
// Template
//=============================================================================

class Processor
{
protected:
    std::string data;

    virtual void getData() = 0;

    void processData() 
    {
        for(int i = 0; i < data.size(); i++)
        {
            data.at(i) += 10;
        }
    }

    void reprData()
    {
        std::cout << data << std::endl;
    }

public:

    void process()
    {
        getData();
        processData();
        reprData();
    }
};

//=============================================================================
// Concrete processors
//=============================================================================

class ConsoleProcessor : public Processor
{
protected:
    void getData() override
    {
        char buffer[300];
        std::cin.getline(buffer, 300);
        data = buffer;
    }
};

//=============================================================================

class FileProcessor : public Processor
{
protected:
    void getData() override
    {
        data = "data_from_file";
    }
};

//=============================================================================
// Run function
//=============================================================================

void run()
{
    ConsoleProcessor conProc;
    conProc.process();

    FileProcessor fileProc;
    fileProc.process();
}



#endif //TEMPLATE_METHOD_H
