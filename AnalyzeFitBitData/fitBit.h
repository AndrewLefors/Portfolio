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
#define _CRT_SECURE_NO_WARNINGS // necessary to ignore scanf_s () warnings (Must come first)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
}Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;

}FitbitData;

typedef struct maxSteps
{
	int steps;
	char* minute;

}MaxSteps;

typedef struct poorSleep
{
	char* startTime;
	char* endTime;
	int sumSleep;

}PoorSleep;

typedef struct report
{
	double totalCalories;
	double distanceInMiles;
	int totalFloors;
	int totalSteps;
	double avgHeartRate;
	MaxSteps stepsTime;
	PoorSleep badSleepRange;

}Report;


//function headers
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
int get_line_count(FILE* infile);

/************************************************************
* Function: read_and_parse_lines()                          *
* Date Created: 5/15/2020                                   *
* Date Last Modified: 5/18/2020                             *
* Description: 1) Reads in entire line from file            *
*              2) Separates data fields, removes duplicates,*
*                 cleanses data                             *
*              3) Assigns data to struct FitbitData fields  *
* Input parameters: 1) pointer to file.                     *
*                   2) pointer to records.                  *
* Returns: Void                                             *
* Preconditions: 1) Data sorted by minute.                  *
*                2) First entry ID is target ID.            *
*				 3) Memory available for FitbitData records.*
* Postconditions: 1) infile points to end of file.          *
*                 2) records holds all but the first line.  *
*************************************************************/
void read_and_parse_lines(FILE* infile, FitbitData records[]);

/************************************************************
* Function: analyze_data ()                                 *
* Date Created: 5/15/2020                                   *
* Date Last Modified: 5/17/2020                             *
* Description: 1) Checks if data is from target ID.         *
*              2) Sums up data fields.                      *
*              3) Finds max steps taken in a minute.        *
*              4) Finds worst sleep range.                  *
*              5) Assigns data to report struct.            *
* Input parameters: 1) struct FitbitData pointer.           *
*                   2) struct Report pointer.               *
*                   3) int file length.                     *
* Returns: Void                                             *
* Preconditions: 1) FitbitData pointer not NULL.            *
				 2) Memory available for struct Report.     *
* Postconditions: 1) report is populated with analyzed data *
*************************************************************/
void analyze_data(FitbitData records[], Report* report, int fileLength);

/************************************************************
* Function: write_display_results ()                        *
* Date Created: 5/15/2020                                   *
* Date Last Modified: 5/18/2020                             *
* Description: 1) Writes data report points to outfile.     *
*              2) Displays data report points to stdout.    *
* Input parameters: Pointer to file, pointer to Report      *
* Returns: Void                                             *
* Preconditions: Pointer to file not NULL                   *
* Postconditions: Overwrites "Results.csv" if not exist     *
*************************************************************/
void write_display_results(FILE* outfile, Report* report);