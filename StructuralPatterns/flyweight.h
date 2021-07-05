#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H
#include <iostream>
#include <vector>
#include <unistd.h>
#define CharMatrix std::vector<std::vector<char> >

//==============================================================================
// Display
//==============================================================================

class Display
{
private:
    CharMatrix field;
    int width;
    int height;

public:
    Display(int width, int height)
    {
        this->width = width;
        this->height = height;
        for(int i = 0; i < height; i++)
        {
            std::vector<char> tmp;
            for(int j = 0; j < width; j++)
            {
                tmp.push_back(' ');
            }
            field.push_back(tmp);
        }
    }

    void draw()
    {
        system("clear");
        for(int i = 0; i < width + 2; i++)
        {
            std::cout << '*';
        }
        std::cout << std::endl;
        for(int i = 0; i < height; i++)
        {
            std::cout << '*';
            for(int j = 0; j < width; j++)
            {
                std::cout << field.at(i).at(j);
            }
            std::cout << '*' << std::endl;
        }
        for(int i = 0; i < width + 2; i++)
        {
            std::cout << '*';
        }
        std::cout << std::endl;
    }

    void addSprite(CharMatrix sprite, int x, int y)
    {
        for(int i = 0; i < sprite.size(); i++)
            for(int j = 0; j < sprite.at(i).size(); j++)
            {
                int xTmp = (j + x) % width;
                int yTmp = (i + y) % height;
                field.at(yTmp).at(xTmp) = sprite.at(i).at(j);
            }
    }

    void reset()
    {
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
            {
                field.at(i).at(j) = ' ';
            }
    }

    ~Display() {}
};

//==============================================================================
// Flyweight
//==============================================================================

class SpriteFlyweight
{
private:
    CharMatrix sprite;
    Display *display;

public:
    SpriteFlyweight(CharMatrix sprite, Display *display)
    {
        this->sprite = sprite;
        this->display = display;
    }

    void drawSprite(int x, int y)
    {
        display->addSprite(sprite, x, y);
    }

    ~SpriteFlyweight() {}
};

//==============================================================================
// Object
//==============================================================================

class Object
{
private:
    int x;
    int y;
    SpriteFlyweight *sprite;

public:
    Object(SpriteFlyweight *sprite, int x = 0, int y = 0)
    {
        this->sprite = sprite;
        this->x = x;
        this->y = y;
    }

    void updatePos(int xShift, int yShift)
    {
        x += xShift;
        y += yShift;
        sprite->drawSprite(x, y);
    }
    ~Object() {}

};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    Display *display;
    display = new Display(15, 15);

    SpriteFlyweight *sprite1;
    sprite1 = new SpriteFlyweight(
                {{'*'}},
                display
            );

    SpriteFlyweight *sprite2;
    sprite2 = new SpriteFlyweight(
                {
                    {'*','*'},
                    {'*','*'}
                },
                display
            );

    std::vector<Object*> objVec;

    objVec.push_back(new Object(sprite1));
    objVec.push_back(new Object(sprite1, 3, 2));
    objVec.push_back(new Object(sprite1, 5, 8));
    objVec.push_back(new Object(sprite1, 12, 11));
    objVec.push_back(new Object(sprite1, 7, 3));
    objVec.push_back(new Object(sprite2, 14, 5));
    objVec.push_back(new Object(sprite2, 0, 10));

    for(int i = 0; i < 100; i++)
    {
        display->reset();
        for(auto obj : objVec)
        {
            obj->updatePos(1, 1);
        }
        display->draw();
        usleep(250 * 1000);
    }

    for(auto obj : objVec)
    {
        delete obj;
    }

    delete sprite1;
    delete sprite2;
    delete display;
}

#endif //FLYWEIGHT_H

