#ifndef DATA_H
#define DATA_H
#include <iostream>
class Data
{
    private:
    std::string command;
    std::string description;

    public:
    Data(void)
    {
        command = "\0";
        description = "\0";
    }

    Data(std::string newCommand, std::string newDescription)
    {
        this->command = newCommand;
        this->description = newDescription;
    }

    ~Data()
    {
        
    }

    void setCommand(std::string newCommand);

    void setDescription(std::string newDescription);

    void printCommand();

    void printDescription();

    std::string* getCommand();

    std::string* getDescription();
};

#endif //DATA_H