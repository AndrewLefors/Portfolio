#ifndef FUNCTIONS_C
#define FUNCTIONS_C

#include "functions.hpp"
#define MIN_TURNS 5
#define MAX_TURNS 30

void loadData(std::string fileName, List<Data> *newList)
{
    std::ifstream inFile(fileName);
    if(inFile)
    {
        while(inFile)
        {
            std::string command = "\0", description = "\0";
            getline(inFile, command, ',');
            getline(inFile, description, '\n');

            Data *newData = new Data(command, description);

            newList->addNode(newData);
        }
    }
    else
    {
        std::cout << "Error: Could not open file" << fileName << std::endl;
        
    }

    inFile.close();
}

int getLines(std::string fileName)
{
    std::ifstream inFile(fileName);
    int count = 0;
    std::string dumbyString;
    if(inFile)
    {
        while(inFile)
        {
            getline(inFile, dumbyString);
            count++;
        }
    }
    inFile.close();
    return count;
}

Profiles* loadProfiles(std::string fileName, int lines)
{
    std::ifstream inFile(fileName);
    Profiles* users = new Profiles[lines];
    int index = 1;
    if(inFile)
    {
        while(inFile && index < lines)
        {
            std::string name = "\0";
            std::string points = "\0";

            getline(inFile, name, ',');
            getline(inFile, points, '\n');

            int score = std::stoi(points);

            users[lines - index].setUserName(name);
            users[lines - index].setUserPoints(score);

            index++;
        }

        
    }
    inFile.close();
    return users;
}

int displayMenu(void)
{
    int option = -1;

    do
    {
  
    
    std::cout << "1: Game Rules" << std::endl;
    std::cout << "2: Play Game" << std::endl;
    std::cout << "3: Load Previous Game" << std::endl;
    std::cout << "4: Add Command" << std::endl;
    std::cout << "5: Remove Command" << std::endl;
    std::cout << "6: Exit" << std::endl;

    std::cin >> option;
    } while(option < 1 || option > 6);

    std::system("pause");
    std::system("clear");

    return option;
}


void playGame(List<Data> *commandList, Profiles *usersArray)
{
    srand(time(NULL));
    std::string descriptionArray[3];
    Node<Data> *iterator = commandList->returnHead();
    std::string newUser = "New User";
    if(*usersArray[0].getUserName() == newUser)
    {
    std::cout << "Enter desired user name: ";
    std::cin >> newUser;
    std::cout << std::endl;
    usersArray[0].setUserName(newUser);
    }

    int turns = 5;
    int round = 1;
    int counter = 0;

    std::cout << "Enter desired question number." << std::endl;
    std::cout << "Cannot be less than 5 or greater than 30." << std::endl;
    do
    {
        std::cin >> turns;

    } while(turns < MIN_TURNS || turns > MAX_TURNS);

    //Start of actual game loop. This has to track which commands have been used.
    int trueFreqArray[turns];
    int falseFreqArrayOne[turns];
    int falseFreqArrayTwo[turns];

    std::string trueDescriptionArray[turns];
    std::string falseDescriptionArrayOne[turns];
    std::string falseDescriptionArrayTwo[turns];

    //set freqArray values to random number to generate random description.
    //One true description (used to match with command) and two false descriptions.
    for (int index = 0; index < turns; index++)
    {
        trueFreqArray[index] = rand() % MAX_TURNS;
        falseFreqArrayOne[index] = rand() % MAX_TURNS;
        falseFreqArrayTwo[index] = rand() % MAX_TURNS;
    }
 
    
    do
{
    pause(2);   
    std::system("clear");
    iterator = commandList->returnHead();
    //Pulls random true command from list
    for (int index = 0; index < trueFreqArray[counter]; index++)
    {
        
        if(iterator->ptrNext != nullptr)
        {
            iterator = iterator->ptrNext;
        }
        else
        {
            iterator = commandList->returnHead();
        }
    }

    std::string* trueDescription = iterator->nodeData->getDescription();
    std::string* trueCommand = iterator->nodeData->getCommand();



    
  
    //Generate fake description one
 
    for (int index = 0; index < falseFreqArrayOne[counter]; index++)
    {
        
        if(iterator->ptrNext != nullptr)
        {
            iterator = iterator->ptrNext;
        }
        else
        {
            iterator = commandList->returnHead();
        }
    }
    
    if(iterator->ptrNext == nullptr)
    {
        iterator = commandList->returnHead();
    }
    
    std::string* falseDescriptionOne = iterator->nodeData->getDescription();

    //Generate fake description two

    for (int index = 0; index < falseFreqArrayTwo[counter]; index++)
    {
        
        if(iterator->ptrNext != nullptr)
        {
            iterator = iterator->ptrNext;
        }
        else
        {
            iterator = commandList->returnHead();
        }
    }
    if(iterator->ptrNext == nullptr)
    {
        iterator = commandList->returnHead();
    }
    std::string* falseDescriptionTwo = iterator->nodeData->getDescription();
    counter++;
    //get real description and two fake in random order
    int freqArrayTwo[3] = {1, 1, 1};
    int trueAnswer = -1;
    int option = -1;
    //generate 0 or 1, 0 for true description, 1 for false. 
    for (int index = 0; index < 3; index++)
    {
        freqArrayTwo[index] = rand () % 2;
    }
    
        if(freqArrayTwo[0] == 0)
            {
                descriptionArray[0] = *trueDescription;
                descriptionArray[1] = *falseDescriptionOne;
                descriptionArray[2] = *falseDescriptionTwo;
                trueAnswer = 1;
            }
        else if(freqArrayTwo[1] == 0)
            {
                descriptionArray[0] = *falseDescriptionOne;
                descriptionArray[1] = *trueDescription;
                descriptionArray[2] = *falseDescriptionTwo;
                trueAnswer = 2;
            }
        else if (freqArrayTwo[2] == 0)
        {
            descriptionArray[0] = *falseDescriptionOne;
            descriptionArray[1] = *falseDescriptionTwo;
            descriptionArray[2] = *trueDescription;
            trueAnswer = 3;
        }
        else
        {
            descriptionArray[0] = *falseDescriptionOne;
            descriptionArray[1] = *trueDescription;
            descriptionArray[2] = *falseDescriptionTwo;
            trueAnswer = 2;
        }
    
    std::cout << std::endl << *trueCommand << std::endl;
    for (int index = 0; index < 3; index++)
    {
        std::cout << index+1 << ": " << descriptionArray[index] << std::endl;
    }
    do
    {
     std::cin >> option;
    }while(option < 1 || option > 3);

    if(option == trueAnswer)
    {
        std::cout << "Correct! " << *trueCommand << " - " << *trueDescription << std::endl; 
        usersArray[0].addUserPoints();
        std::cout << "You have earned 10 Points for a total of: ";
        usersArray[0].printUserScore();
    }
    else
    {
        std::cout << "Incorrect! " << *trueCommand << " - " << *trueDescription << std::endl;
        usersArray[0].subtractUserPoints();
        std::cout << "You have lost 10 points for a total of: ";
        usersArray[0].printUserScore();
    }
    
    round++;

} while(round <= turns);


return;
}



void loadGame(Profiles* usersArray)
{
    std::string userName;
    usersArray[0].setUserPoints(0);
    std::cout << "Enter user name to load saved Profile: ";
    std::cin >> userName;
    std::cout << std::endl;

    for(int index = 0; index < getLines("profiles.csv"); index++)
    {
        if(*usersArray[index].getUserName() == userName)
        {
            usersArray[0].setUserPoints(usersArray[index].getUserScore());
            usersArray[index].setUserName("New User");
        }
    }
    usersArray[0].setUserName(userName);
    

}

void addNewCommand(List<Data> *commandList)
{
    Node<Data> *iterator = commandList->returnHead();
 
    std::string newCommand;
    std::string newDescription;
    int isAdded = 1;

    std::cout << "NOTE: you MUST add ''" "'' around your Inputs" << std::endl;
    std::cout << "Enter New Command to be added: ";
    std::cin >> newCommand; 
    std::cout << "Enter Description for Command: " << std::endl;


    //This first line is required to clear the std::cin buffer of a new line. DO NOT REMOVE
    std::getline(std::cin, newDescription);
    //This line actually grabs the string from the console and assigns it.
    std::getline(std::cin, newDescription);
 



    
    do
    {


        if(*iterator->nodeData->getCommand() == newCommand)
        {
            
            isAdded = 1;
            std::cout << "Error: Command" << newCommand << " already exists." << std::endl;
        }
        else
        {
            isAdded = 0;
        }
        iterator = iterator->ptrNext;


    }while(iterator != nullptr && isAdded != 1);

    if(isAdded == 0)
    {
        Data *newData = new Data(newCommand, newDescription);
        commandList->addNode(newData);

        std::cout << "Successfully added: " << *commandList->returnHead()->nodeData->getCommand() << std::endl;
    }

    return;
}
//WORKS DONT TOUCH
void removeCommand(List<Data> *commandList)
{
    int option = 1;
    do
    {
    
    Node<Data> *iterator = commandList->returnHead();
    std::string commandToDelete;
    std::cout << "Enter Command to be removed: ";
    std::cin >> commandToDelete;
    int isRemoved = 1;

    //check first node
    if(*iterator->nodeData->getCommand() == commandToDelete)
    {
        isRemoved = 0;
    }
    //check remaining nodes
    while(iterator->ptrNext != nullptr && isRemoved != 0)
    {
        
        
        
        if(*iterator->ptrNext->nodeData->getCommand() == commandToDelete)
        {
            isRemoved = 0;
        }
        else
        {   
            iterator = iterator->ptrNext;
        }
        

    } 

    if(isRemoved == 1)
    {
     std::cout << "Error: No command by that name found." << std::endl;
     do{
            std::cout << "0: Enter new Command name." << std::endl;
            std::cout << "1: Exit Command Removal." << std::endl;
            std::cin >> option;
        } while(option < 0 || option > 1);
    }
    else if(isRemoved == 0)
    {
            Node<Data> *tmp = iterator->ptrNext;
            iterator->ptrNext = iterator->ptrNext->ptrNext;
            delete tmp;
            option = 1;
            std::cout << commandToDelete << " was successfully deleted!" << std::endl;
    }
    
    } while(option != 1);
    
}
//WORKS DONT TOUCH
int exitGame(List<Data> *commandList, Profiles *users)
{
    Node<Data> *iterator = commandList->returnHead();
    int index = getLines("profiles.csv");
    std::ofstream outfileProfiles("profiles.csv");
    std::ofstream fileCommands("commands.csv");

    while(iterator != nullptr)
    {
        if(*iterator->nodeData->getCommand() != "")
        {
       fileCommands <<  *iterator->nodeData->getCommand() << "," << *iterator->nodeData->getDescription() << std::endl;
        }
       iterator = iterator->ptrNext;
    }

    for(int i = 0; i < index; i++)
    {
        if(*users[i].getUserName() != "New User")
        {
        outfileProfiles << *users[i].getUserName() << "," << users[i].getUserScore() << std::endl;
        }
    }


    outfileProfiles.close();
    fileCommands.close();
    commandList->~List();
    return 1;
}


void displayRules(void)
{
    std::cout << "Welcome to the Game of Linux-Command Matching!" << std::endl;
    std::cout << "The rules of the game are:" << std::endl;
    std::cout << "1: A random linux command will print to the screen with 3 Answers." << std::endl;
    std::cout << "2: Be careful! Only one of the answers is correct." << std::endl;
    std::cout << "3: Each correct match gives you 10 points, and each incorrect guess you lose 10 points." << std::endl;
    std::cout << "4: To add new commands to the list, use the Add Command feature and follow the dialogue." << std::endl;
    std::cout << "5: To remove an existing command from the list, use the Remove Command feature and follow the dialogue." << std::endl;
    std::cout << "6: Only one profile of any name can be saved at any given time." << std::endl;
    std::cout << "7: There are between 5 and 30 matches in any given game, determined by the user at the start of each game." << std::endl;
    std::cout << "8: BONUS: Some rounds you will be present with duplicate choices, and others with a blank! That's our way of saying, Thanks for Playin!" << std::endl;
}

//Adapted this function from cplusplus.com
void pause(int duration)
{
    int tmp = time(NULL) + duration;

    while(tmp > time(NULL));
}
#endif