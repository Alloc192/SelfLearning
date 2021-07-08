#ifndef CHAIN_OF_RESPONSIBILITY_H
#define CHAIN_OF_RESPONSIBILITY_H
#include <iostream>
#include <string>

//==============================================================================
// Abstract chain element
//==============================================================================

class RequestHandler;

class RequestHandler
{
protected:
    RequestHandler *child = nullptr;

public:
    virtual std::string handle(std::string req) = 0;

    void setChild(RequestHandler *child)
    {
        this->child = child;
    }

    virtual ~RequestHandler() {}
};

//==============================================================================
// Chain elements
//==============================================================================

class HttpHandler : public RequestHandler
{
public:
    std::string handle(std::string req) override
    {
        std::string res;

        if(req.find("port:80") != std::string::npos)
        {
            res = "HTTP handler called.\n";
        }
        else
        {
            res = "Not HTTP request, calling next handler.\n";
            if(child != nullptr)
            {
                res += child->handle(req);
            }
            else
            {
                res += "No handler for requset: " + req;
            }
        }
        return res;
    }

    ~HttpHandler() {}
};

//==============================================================================

class FtpHandler : public RequestHandler
{
public:
    std::string handle(std::string req) override
    {
        std::string res;

        if(req.find("port:21") != std::string::npos)
        {
            res = "FTP handler called.\n";
        }
        else
        {
            res = "Not FTP request, calling next handler.\n";
            if(child != nullptr)
            {
                res += child->handle(req);
            }
            else
            {
                res += "No handler for requset: " + req;
            }
        }
        return res;
    }

    ~FtpHandler() {}
};

//==============================================================================

class SshHandler : public RequestHandler
{
public:
    std::string handle(std::string req) override
    {
        std::string res;

        if(req.find("port:22") != std::string::npos)
        {
            res = "SSH handler called.\n";
        }
        else
        {
            res = "Not SSH request, calling next handler.\n";
            if(child != nullptr)
            {
                res += child->handle(req);
            }
            else
            {
                res += "No handler for requset: " + req;
            }
        }
        return res;
    }

    ~SshHandler() {}
};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    RequestHandler *head;
    head = new HttpHandler();

    RequestHandler *elem1;
    elem1 = new FtpHandler();

    RequestHandler *elem2;
    elem2 = new SshHandler();

    head->setChild(elem1);
    elem1->setChild(elem2);

    std::cout << head->handle("... port:80 ...") << std::endl;
    std::cout << head->handle("... port:21 ...") << std::endl;
    std::cout << head->handle("... port:22 ...") << std::endl;
    std::cout << head->handle("... port:23 ...") << std::endl;

    delete head;
    delete elem1;
    delete elem2;
}

#endif //CHAIN_OF_RESPONSIBILITY_H
