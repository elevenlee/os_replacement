//////////////////////////////////////////////////////////////////
/*
	File Name:		ReplacementUtility.c
	Instructor:		Prof. Mohamed Zahran
	Grader:			Libin Lu
	Author:			Shen Li
	UID:			N14361265
	Department:		Computer Science
	Note:			This ReplacementUtility.c file includes
					First In First Out Function, Second-Chance
					Function, and Least Recently Used Page
					Replacement Function
*/
//////////////////////////////////////////////////////////////////

///////////////HEADER FILES///////////////
#include "Replacement.h"

///////////////FUNCTIONS///////////////
/*First In First Out Page Replacement Function
  Variable Definition:
  -- page_size: total memory size in pages
  Return value: NULL
*/
void firstInFirstOut(unsigned int page_size){
	PAGE_INFO		*node;						//_page_info structure node
	PAGE_INFO		*temp;						//_page_info structure temp
	char			buffer[STRING_SIZE];		//each page information in CHAR*
	unsigned int	number;						//page number

	//Initialize the buffer
	memset(buffer, 0, STRING_SIZE);

	//Start to replace page
	while ((fgets(buffer, STRING_SIZE, in_channel) != NULL)
			&& (strcmp(buffer, LF) != 0)){
		//Get the page number in the reading file
		number = atoi(buffer);
		//Search the page number in running queue
		temp = searchInQueue(run_queue, number);
		//Page number does not exist in running queue
		if (temp == NULL){
			//Malloc for the new page information node
			node = (PAGE_INFO*)malloc(sizeof(PAGE_INFO));
			//Assign the variables (including page number & reference bit & nex pointer)
			node->page_number = number;
			node->reference = false;
			node->next = NULL;
			//Test the running queue is full
			if (isFullQueue(run_queue, page_size)){
				//Delete the first element in running queue
				temp = deleteInQueue(run_queue);
				//Free the first element
				free(temp);
			}
			//Insert the new page at the rear of running queue
			insertInQueue(run_queue, node);
			//Plus page fault number
			page_fault_number++;
		}
		else{
			//Set the reference bit of page as 1
			temp->reference = true;
		}
		//Plus access number
		access_number++;
		//Output the memory map
		printInQueue(run_queue);
	}
	//Output the statistics
	fprintf(out_channel, "%sPercentage of page faults: %.4f%s", LF, (double)page_fault_number / (double)access_number, LF);
	//Clear all elements in running queue
	clearInQueue(run_queue);

	return;
}

/*Second Chance Page Replacement Function
  Variable Definition:
  -- page_size: total memory size in pages
  Return value: NULL
*/
void secondChance(unsigned int page_size){
	PAGE_INFO		*node;						//_page_info structure node
	PAGE_INFO		*temp;						//_page_info structure temp
	char			buffer[STRING_SIZE];		//each page information in CHAR*
	unsigned int	number;						//page number

	//Initialize the buffer
	memset(buffer, 0, STRING_SIZE);

	//Start to replace page
	while ((fgets(buffer, STRING_SIZE, in_channel) != NULL)
			&& (strcmp(buffer, LF) != 0)){
		//Get the page number in the reading file
		number = atoi(buffer);
		//Search the page number in running queue
		temp = searchInQueue(run_queue, number);
		//Page number does not exist in running queue
		if (temp == NULL){
			//Malloc for the new page information node
			node = (PAGE_INFO*)malloc(sizeof(PAGE_INFO));
			//Assign the variables (including page number & reference bit & nex pointer)
			node->page_number = number;
			node->reference = false;
			node->next = NULL;
			//Test the running queue is full
			if (isFullQueue(run_queue, page_size)){
				//Check the first page's reference bit
				while (run_queue->front->reference){
					//Delete the first element in running queue
					temp = deleteInQueue(run_queue);
					//Set the reference bit as 0
					temp->reference = false;
					//Insert at the rear of running queue
					insertInQueue(run_queue, temp);
				}
				//Delete the first element in running queue (it's reference bit is 0)
				temp = deleteInQueue(run_queue);
				//Free the first element
				free(temp);
			}
			//Insert the new page at the rear of running queue
			insertInQueue(run_queue, node);
			//Plus page fault number
			page_fault_number++;
		}
		else{
			//Set the reference bit of page as 1
			temp->reference = true;
		}
		//Plus access number
		access_number++;
		//Output the memory map
		printInQueue(run_queue);
	}
	//Output the statistics
	fprintf(out_channel, "%sPercentage of page faults: %.4f%s", LF, (double)page_fault_number / (double)access_number, LF);
	//Clear all elements in running queue
	clearInQueue(run_queue);

	return;
}

/*Least Recently Used Page Replacement Function
  Variable Definition:
  -- page_size: total memory size in pages
  Return value: NULL
*/
void leastRecentlyUsed(unsigned int page_size){
	PAGE_INFO		*node;						//_page_info structure node
	PAGE_INFO		*temp;						//_page_info structure temp
	char			buffer[STRING_SIZE];		//each page information in CHAR*
	unsigned int	number;						//page number
	unsigned int	memory[STRING_SIZE] = {0};	//memory map array
	unsigned int	count;						//counter

	//Initialize the buffer
	memset(buffer, 0, STRING_SIZE);

	//Start to replace page
	while ((fgets(buffer, STRING_SIZE, in_channel) != NULL)
			&& (strcmp(buffer, LF) != 0)){
		//Get the page number in the reading file
		number = atoi(buffer);
		//Search the page number in running queue
		temp = searchInQueue(run_queue, number);
		//Page number does not exist in running queue
		if (temp == NULL){
			//Malloc for the new page information node
			node = (PAGE_INFO*)malloc(sizeof(PAGE_INFO));
			//Assign the variables (including page number & reference bit & nex pointer)
			node->page_number = number;
			node->reference = false;
			node->next = NULL;
			//Test the running queue is full
			if (isFullQueue(run_queue, page_size)){
				//Delete the first element in running queue
				temp = deleteInQueue(run_queue);
				//Replace the page number
				for (count = 0; count < page_size; count++){
					if (memory[count] == temp->page_number){
						memory[count] = number;
						break;
					}
				}
				//Free the first element
				free(temp);
			}
			else{
				//Insert the page number into memory array
				for (count = 0; count < page_size; count++){
					if (memory[count] == 0){
						memory[count] = number;
						break;
					}
				}
			}
			//Insert the new page at the rear of running queue
			insertInQueue(run_queue, node);
			//Plus page fault number
			page_fault_number++;
		}
		else{
			//Set the reference bit of page as 1
			temp->reference = true;
			//Put the reference page at the rear of the queue
			for (count = 0; count < page_size; count++){
				node = deleteInQueue(run_queue);
				if (node != temp){
					insertInQueue(run_queue, node);
				}
			}
			//Insert the reference page at the rear of the queue
			insertInQueue(run_queue, temp);
		}
		//Plus access number
		access_number++;
		//Output the memory map
		for (count = 0; count < page_size; count++){
			if (memory[count] != 0){
				fprintf(out_channel, "%2u  ", memory[count]);
			}
		}
		fputc('\n', out_channel);
	}
	//Output the statistics
	fprintf(out_channel, "%sPercentage of page faults: %.4f%s", LF, (double)page_fault_number / (double)access_number, LF);
	//Clear all elements in running queue
	clearInQueue(run_queue);

	return;
}
