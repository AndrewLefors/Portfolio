/***************************************************************************************************************************
*                                                                                                                          *
* Created By: Andrew Lefors                                                                                                *
* Created On: 5/15/2020                                                                                                    *
* Assignment: PA-1 'Analyze FitBit Data'                                                                                   *
* Created For: Dr. Guizani CPTS_122 Summer 2020                                                                            *
* File Version: 0.5.15.20                                                                                                  *
* File Description: This program opens a csv-file named "FitbitData.csv", reads in data line-by-line, separates the fields *                                                                                                       *
* 	                checks for duplicates, and cleanses missing valus. Then the data is passed into a struct, analyzed,    *
*                   and results are output to the console and a file "Results.csv"                                         *
*                                                                                                                          *
*       ~  ~                                                                                                               * 
*       @..@                                                                                                               *
*	   (-----)                                                                                                             *
*	  { )_J_( }                                                                                                            *
*	<^>|>   <|<^>                                                                                                          *
****************************************************************************************************************************/

#include "playlistManager.h"


//function definitions

void playlist_menu(void)
{
	Records* playList = NULL;



	int option = -1, dummy;
	do
	{
		
		display_menu();
		
		scanf(" %d", &option);
		
		menu_choice(&option, &playList);
		
	} while (option == -1);
}

void display_menu(void)
{
	
	printf("Select an option from the list below:\n");
	printf("1: Load\n");
	printf("2: Store\n");
	printf("3: Display\n");
	printf("4: Insert\n");
	printf("5: Delete\n");
	printf("6: Edit\n");
	printf("7: Rate\n");
	printf("8: Play\n");
	printf("9: Shuffle\n");
	printf("10: Exit\n");

}

void menu_choice(int* option, Records **headPtr)
{
		switch (*option)
		{
		case 1:

			load(headPtr);
			break;
		case 2:
			if (isEmpty(*headPtr))
			{
				printf("Error: No records to save\n");
				
				break;
			}
			store(headPtr);
			break;
		case 3:
			if (isEmpty(*headPtr))
			{
				printf("Error: No records to display\n");
				
				break;
			}
			display_records(*headPtr);
			break;
		case 4:

			insert(headPtr);
			break;
		case 5:
			if (isEmpty(*headPtr))
			{
				printf("Error: No records to display\n");

				break;
			}
			delete_record(headPtr);
			break;
		case 6:

			edit(headPtr);
			break;
		case 7:

			rate(headPtr);
			break;
		case 8:

			//play();
			break;
		case 9:

			//shuffle();
			break;
		case 10:
			store(headPtr);
			*option = 0;
			return;
		}


	//puts((*headPtr)->filmTitle);
		*option = -1;
		return;
	
}


int isEmpty(Records* recordsPtr)
{
	int status = 0;
	if (recordsPtr == NULL)
		status = 1;

	return status;
}

void clear_screen(void)
{
	//clear the screen
	system("@cls||clear");
}

/************************************************************
* Function: get_line_count()                                *
* Date Created: 5/15/2020                                   *
* Date Last Modified: 5/15/2020                             *
* Description: Gets number of lines in a file               *
* Input parameters: Pointer to file                         *
* Returns: number of lines in file                          *
* Preconditions: pointer to file not NULL                   *
* Postconditions: pointer to file at EOF                    *
*************************************************************/
int get_line_count(FILE* infile)
{
	int count = 0;
	char dummyVar[100];
	while (!feof(infile))
	{
		count += fscanf(infile, "%s\n", dummyVar);
	}
	return count;
}

//DONE DON'T TOUCH AGAIN
void load(Records **recordsPtr)
{
	//declare variables
	char newLine[250];


	FILE* infile = NULL;
	infile = fopen("moviePlayList.csv", "r");
	if (infile == NULL)
	{
		printf("Error: Could not open file\n");
		return;
	}
	//grab header line
	fgets(newLine, 250, infile);
	//grab all data one line at a time until EOF
	while (fgets(newLine, 250, infile) != NULL)
	{
		//appendFrontList(recordsPtr, newLine);
		appendAtFront(recordsPtr, newLine);
	}

	fclose(infile);
	return;
}



//DONE DON'T TOUCH AGAIN
void store(Records** headPtr)
{
	FILE* outfile = NULL;
	outfile = fopen("moviePlayList.csv", "w");
	if (outfile == NULL)
	{
		printf("Error: could not open file\n");
		return;
	}
	Records* current = *headPtr;

	while (current->next != NULL)
		current = current->next;
	fprintf(outfile, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n");
	while (current != NULL)
	{
		fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d,%d\n", current->filmTitle, current->director, current->description, current->genre, current->runningTime.hours, 
			                                             current->runningTime.minutes, current->year, current->playCount, current->rating);
		current = current->prev;
	}
	fclose(outfile);
}
//DONE DON'T TOUCH AGAIN
void display_records(Records* playListRef)
{
	int option = 0, year = -1;
	char directorName[100] = { '\0' }, first[50], last[50];
	printf("1: Display all records.\n");
	printf("2: Display records matching Director Name.\n");
	printf("3: Display records matching year released.\n");
	scanf("%d", &option);

	

	Records* current = playListRef;
	while (current->next != NULL)
		current = current->next;


	if (option == 1)
	{
		while (current != NULL)
		{
			printf("%s,%s,%s,%s,%d:%d,%d,%d,%d\n", current->filmTitle, current->director, current->description, current->genre,
				current->runningTime.hours, current->runningTime.minutes, current->year, current->playCount, current->rating);
			current = current->prev;
		}
	}
	else if (option == 2)
	{
	
		printf("Enter directors name:\n");
	
		fscanf(stdin, "%s", first);
		fscanf(stdin, "%s", last);
		//puts(first);
		//puts(last);

		strcat(directorName, first);
		strcat(directorName, " ");
		strcat(directorName, last);
		puts(directorName);

		while (current != NULL)
		{
			if (strcmp(directorName, current->director) == 0)
			{
				printf("%s,%s,%s,%s,%d:%d,%d,%d,%d\n", current->filmTitle, current->director, current->description, current->genre,
					current->runningTime.hours, current->runningTime.minutes, current->year, current->playCount, current->rating);
			}
			
			current = current->prev;
		}
	}
	else if (option == 3)
	{
		printf("Enter the Year the movie was released:\n");
		scanf("%d", &year);

		while (current != NULL)
		{
			if (year == current->year)
			{
				printf("%s,%s,%s,%s,%d:%d,%d,%d,%d\n", current->filmTitle, current->director, current->description, current->genre,
					current->runningTime.hours, current->runningTime.minutes, current->year, current->playCount, current->rating);
			}
			current = current->prev;
		}
	}
	else
	{
		printf("Error: Your option was not recognized as a valid input.\n");
	}
			
	
	return;
}
//DONE DO NOT TOUCH AGAIN
void insert(Records** headPtr)
{
	
	char movieTitle[25], directorName[25], description[50], genre[10], data[250] = { '\0' }, *title, *name, *desc, *type, *hours, *minutes, *releaseYear, *played, *score;
	char timeHours[10], timeMinutes[10], year[10], playCount[10], rating[10], first[25], last[25];

	Records* newNode = NULL;
	newNode = (Records*)malloc(sizeof(Records));
	if (newNode == NULL)
	{
		printf("Error: Could not allocate memory\n");
		return;
	}
	

	printf("Enter Movie Title: \n");
	getc(stdin);
	fgets(movieTitle, 25, stdin);
	printf("Enter Directors Name: \n");
	//getc(stdin);
	fgets(directorName, 25, stdin);

	
	printf("Enter Movie Description: \n");
	//getc(stdin);
	fgets(description, 100, stdin);
	//getchar(stdin);
	printf("Enter Movie Genre: \n");
	//getc(stdin);
	fgets(genre, 50, stdin);
	//getc(stdin);
	printf("Enter the running time hours: \n");
	//getc(stdin);
	fgets(timeHours, 10, stdin);
	printf("Enter the running time minutes: \n");
	//getc(stdin);
	fgets(timeMinutes, 10, stdin);
	printf("Enter the year the Movie was released: \n");
	//getc(stdin);
	fgets(year, 10, stdin);
	printf("Enter the number of times played: \n");
	//getc(stdin);
	fgets(playCount, 10, stdin);
	printf("Enter a rating for the Movie between 1-5: \n");
	//getc(stdin);
	fgets(rating, 10, stdin);


	//using strtok again to remove newline character at end of each string for insert.
	title = strtok(movieTitle, "\n");
	strcat(data, title);
	strcat(data, ",");
	name = strtok(directorName, "\n");
	strcat(data, name);
	strcat(data, ",");
	desc = strtok(description, "\n");
	strcat(data, desc);
	strcat(data, ",");
	type = strtok(genre, "\n");
	strcat(data, type);
	strcat(data, ",");
	hours = strtok(timeHours, "\n");
	strcat(data, hours);
	strcat(data, ":");
	minutes = strtok(timeMinutes, "\n");
	strcat(data, minutes);
	strcat(data, ",");
	releaseYear = strtok(year, "\n");
	strcat(data, releaseYear);
	strcat(data, ",");
	played = strtok(playCount, "\n");
	strcat(data, played);
	strcat(data, ",");
	score = strtok(rating, "\n");
	strcat(data, score);

	puts(data);
	
	appendAtFront(headPtr, data);


	return;

}

void appendAtFront(Records** playListRef, char *new_data)
{
	char* filmTitle, * director, * description, * genre, * time, * timeHours, 
		* timeMinutes, * year, * playCount, * rating;

	Records* newNode = (Records*)malloc(sizeof(Records));

	filmTitle = strtok(new_data, ",");
	director = strtok(NULL, ",");
	description = strtok(NULL, ",");
	genre = strtok(NULL, ",");
	timeHours = strtok(NULL, ":");
	timeMinutes = strtok(NULL, ",");
	year = strtok(NULL, ",");
	playCount = strtok(NULL, ",");
	rating = strtok(NULL, ",");

	strcpy(newNode->filmTitle, filmTitle);
	strcpy(newNode->director, director);
	strcpy(newNode->description, description);
	strcpy(newNode->genre, genre);
	newNode->runningTime.hours = atoi(timeHours);
	newNode->runningTime.minutes = atoi(timeMinutes);
	newNode->year = atoi(year);
	newNode->playCount = atoi(playCount);
	newNode->rating = atoi(rating);

	//is the llist empty
	if (isEmpty(*playListRef))
	{
		newNode->next = NULL;
		newNode->prev = NULL;
		*playListRef = newNode;

		return;
	}

	Records* current = *playListRef;
	while (current->prev != NULL)
		current = current->prev;

	current->prev = newNode;
	newNode->next = current;
	newNode->prev = NULL;

	*playListRef = current->prev;

}

void delete_record(Records** playListRef)
{
	char movieTitle[100];
	int itemDeleted = 0;
	getc(stdin);
	printf("Enter Movie Title to Delete:\n");

	fgets(movieTitle, 100, stdin);
	puts(movieTitle);
	Records* current = *playListRef;
	while (current->next != NULL)
		current = current->next;
	


	while (current != NULL)
	{
		if (strcmp(current->filmTitle, movieTitle) == 0);
		{
			//checking if at front of list
			if (current->prev == NULL)
			{
			
				(*playListRef) = current->next;
				(*playListRef)->prev = NULL;
				free(current);
				return;
			}
			else if (current->next == NULL)
			{
				
				(*playListRef) = current->prev;
				(*playListRef)->next = NULL;
				free(current);
				return;
			}
			else
			{
				
				(*playListRef) = current->next;
				(*playListRef)->prev = current->prev;
				free(current);
				return;
				
			}
			
		}
	
		current = current->prev;
	}
	return;
}

void edit(Records** playListRef)
{
	char directorName[25], name[25], description[25], title[25], genre[25], timeHours[10], timeMinutes[10], year[10], rating[10], played[10];
	int option = -1;
	printf("Enter the director name for the record you wish to edit\n");
	getc(stdin);

	fgets(directorName, 25, stdin);

	Records* current = *playListRef;
	while (current->next != NULL)
		current = current->next;

	while (current != NULL)
	{
		if (strcmp(directorName, current->director) == 0)
		{
			printf("Edit record for: %s?\n1: Yes\n2: No\n", current->filmTitle);
			getc(stdin);
			scanf("%d", &option);
			if (option == 1)
			{
				printf("Enter Movie Title: \n");
				getc(stdin);
				fgets(title, 25, stdin);
				printf("Enter Directors Name: \n");
				//getc(stdin);
				fgets(directorName, 25, stdin);


				printf("Enter Movie Description: \n");
				//getc(stdin);
				fgets(description, 100, stdin);
				//getchar(stdin);
				printf("Enter Movie Genre: \n");
				//getc(stdin);
				fgets(genre, 50, stdin);
				//getc(stdin);
				printf("Enter the running time hours: \n");
				//getc(stdin);
				fgets(timeHours, 10, stdin);
				printf("Enter the running time minutes: \n");
				//getc(stdin);
				fgets(timeMinutes, 10, stdin);
				printf("Enter the year the Movie was released: \n");
				//getc(stdin);
				fgets(year, 10, stdin);
				printf("Enter the number of times played: \n");
				//getc(stdin);
				fgets(played, 10, stdin);
				printf("Enter a rating for the Movie between 1-5: \n");
				//getc(stdin);
				fgets(rating, 10, stdin);

				strcpy(current->filmTitle, title);
				strcpy(current->director, directorName);
				strcpy(current->description, description);
				strcpy(current->genre, genre);
				current->runningTime.hours = atoi(timeHours);
				current->runningTime.minutes = atoi(timeMinutes);
				current->year = atoi(year);
				current->playCount = atoi(played);
				current->rating = atoi(rating);

			}
			else if (option == 2)
			{
				printf("Checking next record\n");
			}
			else
			{
				printf("Error: input not recognized as valid.\n");
			}
		}
		current = current->prev;
	}
}


void rate(Records** playListRef)
{
	char movieName[50];
	printf("Enter the name of the movie you wish to rate\n");
	getc(stdin);
	fgets(movieName, 50, stdin);

	Records* current = *playListRef;
	while (current->next != NULL)
		current = current->next;

	while (current != NULL)
	{
		if (strcmp(current->filmTitle, movieName) == 0)
		{
			printf("Enter new rating:\n");
			getc(stdin);
			current->rating = scanf("%d");
		}
		current = current->prev;
	}
}