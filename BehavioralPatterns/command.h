#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
#include <vector>

//==============================================================================
// Command interface
//==============================================================================

class Command
{
public:
    virtual void exec(std::string cmd) = 0;
    virtual ~Command() {}
};

//==============================================================================
// Concrete commands
//==============================================================================

class MoveCommand : public Command
{
public:
    void exec(std::string cmd) override
    {
        char arg = cmd[4];
        if(arg == 'U')
        {
            std::cout << "Move up cmd" << std::endl;
        }
        if(arg == 'D')
        {
            std::cout << "Move down cmd" << std::endl;
        }
        if(arg == 'L')
        {
            std::cout << "Move left cmd" << std::endl;
        }
        if(arg == 'R')
        {
            std::cout << "Move right cmd" << std::endl;
        }

    }

    ~MoveCommand() {}
};

//==============================================================================

class ActionCommand : public Command
{
public:
    void exec(std::string) override
    {
        std::cout << "Action cmd" << std::endl;
    }

    ~ActionCommand() {}
};

//==============================================================================
// Command readers
//==============================================================================

class ScriptReader
{
private:
    Command *movCmd;
    Command *actCmd;

public:
    ScriptReader(Command *movCmd, Command *actCmd)
    {
        this->movCmd = movCmd;
        this->actCmd = actCmd;
    }

    void readAndExec()
    {
        std::vector<std::string> commands = {
            "mov D",
            "mov L",
            "act",
            "mov U",
            "mov R"
        };

        for(auto cmd : commands)
        {
            if(cmd.find("mov") != std::string::npos)
            {
                movCmd->exec(cmd);
            }
            else if(cmd.find("act") != std::string::npos)
            {
                actCmd->exec(cmd);
            }
            else
            {
                std::cout << "Command unrecognized" << std::endl;
            }
        }
    }

    ~ScriptReader() {}
};

//==============================================================================

class ConsoleReader
{
private:
    Command *movCmd;
    Command *actCmd;

public:
    ConsoleReader(Command *movCmd, Command *actCmd)
    {
        this->movCmd = movCmd;
        this->actCmd = actCmd;
    }

    void readAndExec()
    {
        std::cout << "For exit enter \":q\"" << std::endl;
        char buff[10];
        while (true)
        {
            std::cin.getline(buff, 10);
            std::string cmd = buff;

            if(cmd.find("mov") != std::string::npos)
            {
                movCmd->exec(cmd);
            }
            else if(cmd.find("act") != std::string::npos)
            {
                actCmd->exec(cmd);
            }
            else if(cmd.find(":q") != std::string::npos)
            {
                break;
            }
            else
            {
                std::cout << "Command unrecognized" << std::endl;
            }
        }
    }

    ~ConsoleReader() {}

};

//==============================================================================
// Run function
//==============================================================================

void run()
{
    Command *actCmd;
    Command *movCmd;
    actCmd = new ActionCommand();
    movCmd = new MoveCommand();

    ScriptReader script(movCmd, actCmd);
    script.readAndExec();

    ConsoleReader console(movCmd, actCmd);
    console.readAndExec();

    delete actCmd;
    delete movCmd;
}

#endif //COMMAND_H
