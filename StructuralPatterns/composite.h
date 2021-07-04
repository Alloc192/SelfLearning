#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <iostream>
#include <vector>
#include <string>

//==============================================================================
// Component interface
//==============================================================================

class Component
{
protected:
    int size;
    std::string name;

public:
    virtual void repr(std::string indent) = 0;
    virtual int getSize() = 0;
    virtual ~Component() {}
};

//==============================================================================
// Components
//==============================================================================

class Directory : public Component
{
private:
    std::vector<Component*> children;

public:
    Directory(std::string name)
    {
        this->name = name;
    }

    void addChild(Component *comp)
    {
        children.push_back(comp);
    }

    int getSize() override
    {
        size = 0;
        for(auto comp : children)
        {
            size += comp->getSize();
        }
        return size;
    }

    void repr(std::string indent) override
    {
        std::cout << indent << "Directory " << name
                  << ", size " << getSize() << std::endl;
        for(auto comp : children)
        {
            comp->repr(indent + "  ");
        }
    }

    ~Directory()
    {
        for (auto comp : children)
        {
            delete comp;
        }
    }
};

//==============================================================================

class File : public Component
{
public:
    File(std::string name, int size)
    {
        this->name = name;
        this->size = size;
    }

    void repr(std::string indent) override
    {
        std::cout << indent << "File " << name
                  << ", size " << size << std::endl;
    }

    int getSize() override
    {
        return size;
    }

    ~File() {};
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    Directory* dir1 = new Directory("Directory 1");
    Directory* dir2 = new Directory("Directory 2");
    Directory* dir3 = new Directory("Directory 3");
    Directory* dir4 = new Directory("Directory 4");

    dir1->addChild(dir2);
    dir1->addChild(dir3);
    dir1->addChild(new File("File_1.txt", 10));

    dir2->addChild(new File("File_2.txt", 11));
    dir2->addChild(new File("File_3.txt", 12));

    dir3->addChild(dir4);
    dir3->addChild(new File("File_4.txt", 13));

    dir4->addChild(new File("File_5.txt", 14));
    dir4->addChild(new File("File_6.txt", 15));

    dir1->repr("");

    delete dir1;
}

#endif // COMPOSITE_H
