#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H
#include <iostream>
#include <string>

//==============================================================================
// Products
//==============================================================================

class IProduct
{
public:
    virtual void repr() = 0;
    virtual ~IProduct() {};
};

//==============================================================================

class Book : public IProduct
{
private:
    std::string name;
    double price;
public:
    Book(std::string name, double price);
    void repr() override;
    ~Book();
};

Book::Book(std::string name, double price)
{
    std::cout << "Book constructor called" << std::endl;
    this->name = name;
    this->price = price;
}

void Book::repr()
{
    std::cout << "It is a book \"" << name
              << "\", costs " << price << std::endl;
}

Book::~Book()
{
    std::cout << "Book destructor called" << std::endl;
}

//==============================================================================

class Magazine : public IProduct
{
private:
    std::string name;
    int year;
    double price;
public:
    Magazine(std::string name, int year, double price);
    void repr() override;
    ~Magazine();
};

Magazine::Magazine(std::string name, int year, double price)
{
    std::cout << "Magazine constructor called" << std::endl;
    this->name = name;
    this->year = year;
    this->price = price;
}

void Magazine::repr()
{
    std::cout << "It is a magazine \"" << name
              << "\"" << year
              << ", costs " << price << std::endl;
}

Magazine::~Magazine()
{
    std::cout << "Magazine destructor called" << std::endl;
}

//==============================================================================
// Factories
//==============================================================================

class Factory
{
public:
    virtual IProduct* create() = 0;
    virtual ~Factory() {};
};

//==============================================================================

class BookFactory : public Factory
{
public:
    IProduct* create() override;
    ~BookFactory() {};
};

IProduct* BookFactory::create()
{
    IProduct *prod;
    prod = new Book("Book 1", 19.25);
    return prod;
}

//==============================================================================

class MagazineFactory : public Factory
{
public:
    IProduct* create() override;
    ~MagazineFactory() {};
};

IProduct* MagazineFactory::create()
{
    IProduct *prod;
    prod = new Magazine("Magazine 1", 2009, 2.99);
    return prod;
}

//==============================================================================
// Run function
//==============================================================================

void run()
{
    Factory *factory;
    IProduct *product;

    factory = new BookFactory();
    product = factory->create();
    product->repr();
    delete product;
    delete factory;

    factory = new MagazineFactory();
    product = factory->create();
    product->repr();
    delete product;
    delete factory;
}
#endif // FACTORY_METHOD_H
