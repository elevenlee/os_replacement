//////////////////////////////////////////////////////////////////
/*
	File Name:		PageUtility.c
	Instructor:		Prof. Mohamed Zahran
	Grader:			Libin Lu
	Author:			Shen Li
	UID:			N14361265
	Department:		Computer Science
	Note:			This PageUtility.c file includes
					Initialize Page Information, Clear Page
					Information, and Name Output File Functions.
*/
//////////////////////////////////////////////////////////////////

///////////////HEADER FILES///////////////
#include "Replacement.h"

///////////////FUNCTIONS///////////////
/*Initialize Page Information Function
  Variable Definition:
  -- file_name: reading file name
  -- method: page replacement method
  Return value: NULL
*/
void initPageInfo(const char *file_name, const char *method){
	//Get the output file's name
	nameOutputFile(file_name, method);
	//Open file for reading page information
	if ((in_channel = fopen(file_name, "r")) == NULL){
		dieWithUserMessage("fopen() failed", "cannot open file to read page information!");
	}
	//Open file for write replacement result(memory map and statistics)
	if ((out_channel = fopen(name, "w")) == NULL){
		dieWithUserMessage("fopen() failed", "cannot open file to write replacement result!");
	}
	//Malloc memory for _page_queue_structure
	run_queue = (PAGE_QUEUE*)malloc(sizeof(PAGE_QUEUE));
	//Initialize the running queue
	initQueue(run_queue);
	//Initialize the access number
	access_number = 0;
	//Initialize the page fault number
	page_fault_number = 0;

	return;
}

/*Clear Page Information Function
  Variable Definition:
  -- NULL
  Return value: NULL
*/
void clearPageInfo(){
	//Close read file
	fclose(in_channel);
	//Close write file
	fclose(out_channel);
	//Free the _page_queue structure
	free(run_queue);

	return;
}

/*Name Output File Function
  Variable Definition:
  -- file_name: reading file name
  -- method: page replacement method
  Return value: NULL
*/
void nameOutputFile(const char *file_name, const char *method){
	char	*extension = NULL;		//file extension

	//Malloc memory for output file name
	name = (char*)malloc(sizeof(char) *(NAME_SIZE + 1));
	//Copy the input file name to output file
	strcpy(name, file_name);
	//Search the input file's name (exclude the file type)
	if ((extension = strrchr(name, '.')) != NULL){
		*extension = '\0';
	}
	//Name the output file based on replacement method
	strcat(name, ".");
	strcat(name, method);
	
	return;
}
