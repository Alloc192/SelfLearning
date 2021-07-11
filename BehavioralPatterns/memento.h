#ifndef MEMENTO_H
#define MEMENTO_H
#include <iostream>
#include <vector>
#include <string>

//=============================================================================
// Memento interface
//=============================================================================

class Memento
{
protected:
    std::string name;

public:
    virtual std::string getName() = 0;
    virtual ~Memento() {}
};

//=============================================================================
// Concrete memento
//=============================================================================

class TextMemento : public Memento
{
private:
    std::string data;
    static int id;

public:
    TextMemento(std::string data)
    {
        this->data = data;
        std::string tmp = "000";
        tmp.at(2) += id++;
        this->name = "Text save " + tmp;
    }
    
    std::string getName() override
    {
        return name;
    }

    std::string getData()
    {
        return data;
    }

    ~TextMemento() {}
}; 

int TextMemento::id = 0;

//=============================================================================
// Text edit
//=============================================================================

class TextEdit
{
private:
    std::string data;

public:
    TextEdit(std::string data)
    {
        this->data = data;
    }

    Memento* editText(std::string addition)
    {
        TextMemento* tmp;
        tmp = new TextMemento(data);
        data += addition;
        return tmp;
    }

    void restoreState(Memento *save)
    {
        std::cout << "Restoring data from save " << save->getName() << std::endl;
        TextMemento *tmp = dynamic_cast<TextMemento*>(save);
        data = tmp->getData();
    }

    std::string getData() 
    {
        return data;
    }

    ~TextEdit() {}
};

//=============================================================================
// Run function
//=============================================================================

void run()
{
    std::vector<Memento*> saves;
    TextEdit editor("Some text ");

    for(int i = 0; i < 10; i++)
    {
        saves.push_back(editor.editText("a"));
    }
    std::cout << editor.getData() << std::endl;

    for(int i = 9; i >= 0; i--)
    {
        editor.restoreState(saves.at(i));
        std::cout << editor.getData() << std::endl;
    }

    for (int i = 0; i < 10; i++)
    {
        delete saves.at(i);
    }
}

#endif //MEMENTO_H