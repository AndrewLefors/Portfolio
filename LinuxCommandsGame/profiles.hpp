#ifndef PROFILES_H
#define PROFILES_H

#include <iostream>


class Profiles
{
    private:
    std::string userName;
    int points;

    public:

    Profiles(void)
    {
     this->userName = "New User";
     this->points = 0;
    }
    Profiles(std::string &name, int &score)
    {
        this->userName = name;
        this->points = score;
    }
    ~Profiles(void)
    {
        delete this;
    }

    void setUserName(std::string newName)
    {
        this->userName = newName;
    }

    void setUserPoints(int points)
    {
        this->points = points;
    }

    void printUserName(void)
    {
        std::cout << this->userName << std::endl;
    }

    void printUserScore(void)
    {
        std::cout << this->points << std::endl;
    }

    void addUserPoints(void)
    {
        this->points = this->points + 10;
    }

    void subtractUserPoints(void)
    {
        this->points = this->points - 10;
    }

    std::string *getUserName(void)
    {
        return &this->userName;
    }

    int getUserScore(void)
    {
        return this->points;
    }
    

};










#endif 