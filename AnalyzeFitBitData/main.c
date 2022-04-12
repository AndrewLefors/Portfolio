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

#include "fitBit.h"

int main(void)
{

	//null file pointer
	FILE* infile = NULL, *outfile = NULL;
	//assign infile to FitbitData
	infile = fopen("FitbitData.csv", "r");
	//check if file opened
	if (infile == NULL)
	{
		return -1;
	}
	//getting number of lines from file
	int lineCount = 0;
	lineCount = get_line_count(infile);
	//check if file empty
	if (lineCount < 1)
	{
		printf("No data to parse\n");
		return 0;
	}
	//return to begining of file
	rewind(infile);
	
	//dynamically allocating memory for fitbit data records of size lineCount
	FitbitData *records = NULL;
	records = (FitbitData*)malloc((sizeof(FitbitData) * lineCount));
	//check if memory was allocated
	if (records == NULL)
	{
		printf("Could not allocate memory\n");
		return -2;
	}

	
	
	//read in and parse lines
	read_and_parse_lines(infile, records);
	fclose(infile);

	//allocate memory for analyzed data
	Report *report = NULL;
	report = (Report*)malloc(sizeof(Report));
	//check if memory allocated
	if (report == NULL)
	{
		printf("Could not allocate memory\n");
		return -2;
	}

	//anayze data and dedupe
	analyze_data(records, report, lineCount);

	//open file to write report to
	outfile = fopen("Results.csv", "w");

	////write to file
	write_display_results(outfile, report);
	
	//freeing up memory from the heap (dynamically allocated memory)
	free(records);
	free(report);
	//close outfile
	fclose(outfile);


	return 0;
}