/***************************************************************************************************************************
*                                                                                                                          *
* Created By: Andrew Lefors                                                                                                *
* Created On: 5/15/2020                                                                                                    *
* Project: FitBit Data Analysis                                                                                            *
* File Version: 0.5.15.20                                                                                                  *
* File Description: This program opens a csv-file named "FitbitData.csv", reads in data line-by-line, separates the fields *                                                                                                       *
* 	                checks for duplicates, and cleanses missing valus. Then the data is passed into a struct, analyzed,*
*                   and results are output to the console to a file "Results.csv"                                          *
*                                                                                                                          *
*           ~  ~                                                                                                           *
*           @..@                                                                                                           *
*	   (-----)                                                                                                         *
*	  { )_J_( }                                                                                                        *
*	<^>|>   <|<^>                                                                                                      *
****************************************************************************************************************************/
#include "fitBit.h"

//Function Definitions


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

void read_and_parse_lines(FILE* infile, FitbitData records[])
{
	//declare variables
	char string[100], *patient, *minute, *calories, *distance, *floors, *heartRate, *steps, *sleepLevel,  *ptr;
	
	
	//set index
	int index = 0, isDuplicate = 0;
	//remove file header
	fgets(string, 100, infile);
	//grab all data one line at a time until EOF
	while (fgets(string, 100, infile) != NULL)
	{
		isDuplicate = 0;
		//parse data componenets from file: CSV-use ","/, TAB-use "\t"
		//no need to check for null value, will be filtered later if ID not found
		patient = strtok(string, ",");
		//check if first value to stay in bounds of array, remove any duplicate entries appearing successively.  
		//Would not catch duplicates if the items are not sorted by minute in file
		minute = strtok(NULL, ",");
		if (records[index - 1].minute != NULL && strcmp(minute, records[index - 1].minute) == 0)
			isDuplicate = 1;
		//check if missing value, substitute invalid input
		calories = strtok(NULL, ",");
		if (strcmp(calories, "") == 0)
			strcpy(calories, "0");
		distance = strtok(NULL, ",");
		if (strcmp(distance, "") == 0)
			strcpy(distance, "0");
		floors = strtok(NULL, ",");
		if (strcmp(floors, "") == 0)
			strcpy(floors, "0");
		heartRate = strtok(NULL, ",");
		if (strcmp(heartRate, "") == 0)
			strcpy(calories, "0");
		steps = strtok(NULL, ",");
		if (strcmp(steps, "") == 0)
			strcpy(steps, "0");
		//check sleepLevel below, had issues directly comparing string
		sleepLevel = strtok(NULL, ",");

		//////////////////////////////////////////////////////////////
		///*COULD SPLIT READING/CLEANSING INTO DISTINCT FUNCTIONS*///
		/////////////////////////////////////////////////////////////
		if (isDuplicate == 0)
		{
			//copy values into records struct
			strcpy(records[index].patient, patient);
			strcpy(records[index].minute, minute);
			//convert strings to double prior to assignment
			records[index].calories = strtod(calories, &ptr);
			records[index].distance = strtod(distance, &ptr);
			//convert strings to int prior to assignment
			records[index].floors = atoi(floors);
			records[index].heartRate = atoi(heartRate);
			records[index].steps = atoi(steps);
			//check and cleanse data
			if (sleepLevel == NULL || atoi(sleepLevel) < 0 || atoi(sleepLevel) > 3)
			{
				records[index].sleepLevel = NONE;
			}
			else
			{
				records[index].sleepLevel = atoi(sleepLevel);
			}
		}
		//increment index to retain all data in struct array
		index = index + 1;
	}

	
}

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
void analyze_data(FitbitData records[], Report *report, int fileLength)
{
	double sumCalories = 0.0, sumDistanceMiles = 0.0, avgHeartRate = 0.0;
	int sumFloors = 0, sumSteps = 0, timePoints = 0, sumHeartRate = 0, poorSleep = 0, worstSleep = 0, counterIndex = 0;
	//set initial steps to 0
	report->stepsTime.steps = 0;

	for (int index = 0; index < fileLength; index++)
	{
		//check for target ID
		if (strcmp(records[index].patient, records[0].patient) == 0)
		{
			//sum up data fields
			sumCalories += records[index].calories;
			sumDistanceMiles += records[index].distance; 
			sumFloors += records[index].floors;
			sumSteps += records[index].steps;
			sumHeartRate += records[index].heartRate;
			//increment time points for average heart rate over time period
			timePoints += 1;
			//finds max steps taken in a minute and the time
			if (report->stepsTime.steps < records[index].steps)
			{
				report->stepsTime.steps = records[index].steps;
				report->stepsTime.minute = records[index].minute;
			}
			//finds worst sleep cycle
			if (records[index].sleepLevel > 1)
			{
				//sum of all sleep levels consecutively above 1
				poorSleep += records[index].sleepLevel;
				//compare worst on record with new value
				if (worstSleep < poorSleep)
				{
					//replace old start time with new start time: Counter index used to retain start time
					report->badSleepRange.startTime = records[index - counterIndex].minute;
					report->badSleepRange.endTime = records[index].minute;
					//replace old worst value with new max
					worstSleep = poorSleep;
				}
				//increment counterindex for start time. MUST come after to not go outside bounds of array
				counterIndex += 1;
			}
			else
			{
				//reset values
				poorSleep = 0;
				counterIndex = 0;
			}
		}
	}
	//compute average heart rate from the sum total and incremented time points
	avgHeartRate = (sumHeartRate / timePoints);
	//assign analyzed data to struct Report fields
	report->avgHeartRate = avgHeartRate;
	report->distanceInMiles = sumDistanceMiles;
	report->totalCalories = sumCalories;
	report->totalFloors = sumFloors;
	report->totalSteps = sumSteps;
}

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
void write_display_results(FILE *outfile, Report* report)
{
	//write to file
	fputs("Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n", outfile);
	fprintf(outfile, "%lf, %lf, %d, %d, %lf, %d, %s:%s\n", report->totalCalories, report->distanceInMiles, report->totalFloors,
		report->totalSteps, report->avgHeartRate, report->stepsTime.steps, report->badSleepRange.startTime, report->badSleepRange.endTime);
	//print to screen
	fputs("Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n", stdout);
	fprintf(stdout, "%lf, %lf, %d, %d, %lf, %d, %s:%s\n", report->totalCalories, report->distanceInMiles, report->totalFloors,
		report->totalSteps, report->avgHeartRate, report->stepsTime.steps, report->badSleepRange.startTime, report->badSleepRange.endTime);
}
