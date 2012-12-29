///////////////////////////////////////////////
/*
	File Name:		MainFunction.c
	Instructor:		Prof. Mohamed Zahran
	Grader:			Libin Lu
	Author:			Shen Li
	UID:			N14361265
	Department:		Computer Science
	Note:			This MainFunction.c file
					includes Main Function.
*/
///////////////////////////////////////////////

///////////////HEADER FILES///////////////
#include "Replacement.h"

///////////////FUNCTIONS///////////////
/*Main Function
  Variable Definition:
  -- argc: the number of command arguments
  -- argv[]: each vairable of command arguments(argv[0] is the path of execution file forever)
  Return Value: exit number
*/
int main(int argc, char *argv[]){
	//Test for correct number of arguments
	if (argc != 4){
		dieWithUserMessage("Parameter(s)", "<Replacement method> <Number of page> <Input file name>");
	}

	char			*file_name = argv[3];			//input file name
	unsigned int	method = atoi(argv[1]);			//replacement method
	unsigned int	page_size = atoi(argv[2]);		//memory size in pages

	//Test for correct page number
	if (page_size <= 0){
		dieWithUserMessage("Page sizes error", "page sizes should be a positive non-zero number!");
	}

	// According to method, start to replace page
	switch (method){
		//First in first out page replacement algorithm
		case 0:
			initPageInfo(file_name, "fifo");
			firstInFirstOut(page_size);
			break;
		//Second-Chance page replacement algorithm
		case 1:
			initPageInfo(file_name, "second");
			secondChance(page_size);
			break;
		//Least recently used replacement algorithm
		case 2:
			initPageInfo(file_name, "lru");
			leastRecentlyUsed(page_size);
			break;
		//Method could not allowed
		default:
			dieWithUserMessage("Method not allowed!", "Please input 0, 1 or 2!");
			break;
	}
	printf("Page replacement success! The result is in %s file.%s", name, LF);
	//Clear page information
	clearPageInfo();

	return 0;
}
