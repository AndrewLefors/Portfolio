#ifndef DATA_C
#define DATA_C

#include "data.hpp"

void Data::setCommand(std::string newCommand)
{
    this->command = newCommand;
}

void Data::setDescription(std::string newDescription)
{
    this->description = newDescription;
}

void Data::printCommand(void)
{
    std::cout << command << std::endl;
}

void Data::printDescription(void)
{
    std::cout << description << std::endl;
}

std::string* Data::getCommand()
{
    return &this->command;
}

std::string* Data::getDescription()
{
    return &this->description;
}









#endif