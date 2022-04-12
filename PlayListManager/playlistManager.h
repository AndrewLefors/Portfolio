/***************************************************************************************************************************
*                                                                                                                          *
* Created By: Andrew Lefors                                                                                                *
* Created On: 5/20/2020                                                                                                    *
* Project: Playlist Manager                                                                                                *
* File Version: 0.5.20.20                                                                                                  *
* File Description: This program opens a csv-file named "moviePlayList.csv", reads in data line-by-line, separates fields, *                                                                                                       *
* 	            checks for duplicates, and organizes the results. The list can be updated in the program without taking*
*                   effect until the program is finished to reduce write time. List can be dynamically updated.            *
*                                                                                                                          *
*           ~  ~                                                                                                           *
*           @..@                                                                                                           *
*	   (-----)                                                                                                         *
*	  { )_J_( }                                                                                                        *
*	<^>|>   <|<^>                                                                                                      *
****************************************************************************************************************************/

#ifndef PLAYLIST_MANAGER
#define _CRT_SECURE_NO_WARNINGS
#define PLAYLIST_MANAGER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct definitions

typedef struct duration
{
	int hours;
	int minutes;
}Duration;

typedef struct records
{
	char filmTitle[100];
	char director[100];
	char description[300];
	char genre[100];
	Duration runningTime;
	int year;
	int playCount;
	int rating;
	struct records* next;
	struct records* prev;

}Records;


//function declarations
/************************************************************
* Function: playlist_menu()                                *
* Date Created: 5/21/2020                                   *
* Date Last Modified: 5/21/2020                             *
* Description:                *
* Input parameters:                          *
* Returns:                           *
* Preconditions:                    *
* Postconditions:                     *
*************************************************************/

void playlist_menu(void);

void display_menu(void);

void menu_choice(int* option, Records** headPtr);

void clear_screen(void);

void load(Records* recordsPtr);

void store(Records** headPtr);

void display_records(Records** headPtr); // input file

void insert(Records** headPtr);

void delete_playlist(void); // input file

void edit(void);

void rate_movie(void);

void play(void);

void shuffle(void);

void exit_program(void);

void insert_at_front(FILE* infile, Records** recordsPtr, char* data);

void appendAtFront(Records** playListRef, char* new_data);

void appendFrontList(Records** head_ref, char* new_data);

void press_key_to_continue(void);

void delete_record(Records** playListRef);

void edit(Records** playListRef);

void rate(Records** playListRef);

#endif //PLAYLIST_MANAGER
