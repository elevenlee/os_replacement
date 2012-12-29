////////////////////////////////////////////////////////////////
/*
	File Name:		Replacement.h
	Instructor:		Prof. Mohamed Zahran
	Grader:			Libin Lu
	Author:			Shen Li
	UID:			N14361265
	Department:		Computer Science
	Note:			This Replacement.h file includes
					HEADER FILES, MACRO, STRUCT DEFINITION,
					GLOBAL VARIABLE AND FUNCTION DECLARATION.
*/
////////////////////////////////////////////////////////////////

///////////////PRECOMPILER///////////////
#ifndef	REPLACEMENT_H_
#define REPLACEMENT_H_

///////////////DEBUG///////////////
//#define	DEBUG 1
#ifdef	DEBUG
	#define DEBUG_PRINT printf("%s-%s:%d:", __FILE__, __FUNCTION__, __LINE__)
#else
	#define DEBUG_PRINT
#endif

///////////////HEADER FILES///////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

///////////////MACRO///////////////
#define	LF	"\n"

///////////////STRUCT DEFINITION///////////////
/*page information structure*/
typedef struct _page_info{
	unsigned int		page_number;	//page number
	bool				reference;		//reference bit
	struct _page_info	*next;			//next pointer
}PAGE_INFO;

/*page replacement queue structure*/
typedef struct _page_queue{
	PAGE_INFO	*front;					//queue front pointer
	PAGE_INFO	*rear;					//queue rear pointer
	PAGE_INFO	*head;					//queue head pointer
}PAGE_QUEUE;

///////////////GLOBAL VARIABLE///////////////
PAGE_QUEUE		*run_queue;				//running queue
FILE			*in_channel;			//read file stream
FILE			*out_channel;			//write file stream
char			*name;					//write file name
unsigned int	access_number;			//access number
unsigned int	page_fault_number;		//page fault number
enum			size_constants{			//size constants
	STRING_SIZE		= 16,
	NAME_SIZE		= 64,
};

///////////////FUNCTION DECLARATION///////////////
/*PageUtility.c*/
void	initPageInfo(const char *file_name, const char *method);
void	clearPageInfo();
void	nameOutputFile(const char *file_name, const char *method);
/*ReplacementUtility.c*/
void	firstInFirstOut(unsigned int page_size);
void	secondChance(unsigned int page_size);
void	leastRecentlyUsed(unsigned int page_size);
/*QueueUtility.c*/
void	initQueue(PAGE_QUEUE *q);
bool	notEmptyQueue(PAGE_QUEUE *q);
bool	isFullQueue(PAGE_QUEUE *q, unsigned int queue_length);
void	insertInQueue(PAGE_QUEUE *q, PAGE_INFO *node);
PAGE_INFO	*deleteInQueue(PAGE_QUEUE *q);
PAGE_INFO	*peekInQueue(PAGE_QUEUE *q);
PAGE_INFO	*searchInQueue(PAGE_QUEUE *q, unsigned int page_number);
void	clearInQueue(PAGE_QUEUE *q);
void	printInQueue(PAGE_QUEUE *q);
/*DieWithMessage.c*/
void	dieWithUserMessage(const char *message, const char *detail);
void	dieWithSystemMessage(const char *message);

#endif //REPLACEMENT_H
