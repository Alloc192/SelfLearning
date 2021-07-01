#ifndef SINGLETON_H
#define SINGLETON_H
#include <iostream>
#include <string>

//==============================================================================
//
//==============================================================================

class FileReader;

class FileMananger
{
private:
    static FileMananger* instance;
    std::string filepath;
    FileMananger() {};


public:
    static FileMananger* getInstance()
    {
        if(instance == nullptr)
        {
            instance = new FileMananger;
        }
        return instance;
    }

    void setFilePath(std::string filepath)
    {
        this->filepath = filepath;
    }

    void repr()
    {
        std::cout << "File manager at " << this
                  << " with filepath " << filepath << std::endl;
    }

    ~FileMananger() {}
};

FileMananger* FileMananger::instance = nullptr;

//==============================================================================
// Run function
//==============================================================================

void run()
{
    FileMananger *fileMan1;
    fileMan1 = FileMananger::getInstance();
    fileMan1->setFilePath("/path/to/file.dir1");

    FileMananger *fileMan2;
    fileMan2 = FileMananger::getInstance();
    fileMan2->setFilePath("/path/to/file.dir1");

    fileMan1->repr();
    fileMan2->repr();

    fileMan2->setFilePath("/path/to/file.dir2");

    fileMan1->repr();
    fileMan2->repr();
}

#endif // SINGLETON_H

