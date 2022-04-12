#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include "data.hpp"
#include "list.hpp"
#include "node.hpp"
#include "profiles.hpp"
void loadData(std::string fileName, List<Data> *newList);

int getLines(std::string fileName);

Profiles* loadProfiles(std::string fileName, int lines);

int displayMenu(void);

void playGame(List<Data> *commandList, Profiles *usersArray);

void loadGame(Profiles* usersArray);

void addNewCommand(List<Data> *commandList);

void removeCommand(List<Data> *commandList);

int exitGame(List<Data> *commandList, Profiles *users);

void displayRules(void);

void pause(int duration);

#endif 