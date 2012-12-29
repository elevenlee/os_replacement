////////////////////////////////////////////////////////////////
/*
	File Name:		QueueUtility.c
	Instructor:		Prof. Mohamed Zahran
	Grader:			Libin Lu
	Author:			Shen Li
	UID:			N14361265
	Department:		Computer Science
	Note:			This QueueUtility.c file includes
					Handle Queue(s) Function.
*/
////////////////////////////////////////////////////////////////

///////////////HEADER FILES///////////////
#include "Replacement.h"

///////////////FUNCTIONS///////////////
/*Initialize _page_queue structure Function
  Variable Definition:
  -- q: _page_queue structure
  Return value: NULL
*/
void initQueue(PAGE_QUEUE *q){
	//front and rear are NULL
	q->front = q->rear = NULL;
	//head is also NULL
	q->head = NULL;

	return;
}

/*Test Queue is not Empty Function
  Variable Definition:
  -- q: _page_queue structure
  Return value: if the queue is not empty return true; else return false
*/
bool notEmptyQueue(PAGE_QUEUE *q){
	//front pointer is NULL
	if (q->front == NULL){
		return false;
	}
	else{
		return true;
	}
}

/*Test Queue is not Full Function
  Variable Definition:
  -- q: _page_queue structure
  -- queue_length: the length of queue
  Return value: if the queue is full return true; else return false
*/
bool isFullQueue(PAGE_QUEUE *q, unsigned int queue_length){
	PAGE_INFO		*node;				//_page_info structure node
	unsigned int	counter = 0;		//queue length counter

	//Test the queue is not empty
	if (q->front != NULL){
		//Set the node as the first element in queue
		node = q->front;
		//Calculate the length of queue
		while (node != q->rear){
			counter++;
			node = node->next;
		}
		counter++;
	}

	return (counter == queue_length);
}

/*Insert an Element in Queue Function
  Variable Definition:
  -- q: _page_queue structure
  -- node: _page_info structure node need to be insert
  Return value: NULL
*/
void insertInQueue(PAGE_QUEUE *q, PAGE_INFO *node){
	//Test the queue is empty
	if (q->front == NULL){
		//Insert the element in the front
		q->front = q->rear = node;
	}
	//Insert the element in the rear
	else{
		q->rear = q->rear->next = node;
	}

	//Set the queue's head pointer
	if (q->head == NULL){
		q->head = node;
	}

	return;
}

/*Delete the First Element in Queue Function
  Variable Definition:
  -- q: _page_queue structure
  Return value: first element in queue
*/
PAGE_INFO *deleteInQueue(PAGE_QUEUE *q){
	PAGE_INFO	*node;		//_page_info structure node

	//Test the queue is empty
	if (q->front == NULL){
		dieWithUserMessage("deleteInQueue() failed", "cannot delete an element in queue!");
	}
	//Set the node as the front element in queue
	node = q->front;
	//Set the queue's front pointer
	q->front = node->next;
	//Test the queue is empty
	if (q->front == NULL){
		q->rear = NULL;
	}
	//Set the queue's head pointer
	if (node == q->head){
		q->head = NULL;
	}
	//Set the next pointer as NULL
	node->next = NULL;

	return node;
}

/*Get the Front Element in Queue Function
  Variable Definition:
  -- q: _page_queue structure
  Return value: first element in queue
*/
PAGE_INFO *peekInQueue(PAGE_QUEUE *q){
	//Test the queue is empty
	if (q->front == NULL){
		return NULL;
	}
	
	return q->front;
}

/*Search the Element in Queue Function
  Variable Definition:
  -- q: _page_queue structure
  -- page_number: page number
  Return value: page number node; if page number do not exist, return NULL
*/
PAGE_INFO *searchInQueue(PAGE_QUEUE *q, unsigned int page_number){
	PAGE_INFO	*node;		//_page_info structure node

	//Set the node as the first element in queue
	node = q->front;
	//Search the page number
	while (node != NULL){
		if (node->page_number == page_number){
			break;
		}
		node = node->next;
	}

	return node;
}

/*Clear all Elements in Queue Function
  Variable Definition:
  -- q: _page_queue structure
  Return value: NULL
*/
void clearInQueue(PAGE_QUEUE *q){
	PAGE_INFO	*node;		//_page_info structure node

	//Set the node as the front element in queue
	node = q->front;
	//Clear all elements in queue
	while (node != NULL){
		q->front = q->front->next;
		free(node);
		node = q->front;
	}
	//Set the queue's rear pointer as NULL
	q->rear = NULL;

	return;
}

/*Print all elements in Queue Function
  Variable Definition:
  -- q: _page_queue structure
  Return value: NULL
*/
void printInQueue(PAGE_QUEUE *q){
	PAGE_INFO	*node;		//_page_info structure node

	//Set the node as the queue's head pointer
	node = q->head;
	//Output the element(s) after the head pointer
	while (node != NULL){
		fprintf(out_channel, "%2u  ", node->page_number);
		node = node->next;
	}
	//Set the node as the queue's front pointer
	node = q->front;
	//Output the rest element(s)
	while (node != q->head){
		fprintf(out_channel, "%2u  ", node->page_number);
		node = node->next;
	}

#ifdef	DEBUG	//Output the FIFO
	fputs("\r\t\tFIFO: ", out_channel);
	//Set the node as the queue's front pointer
	node = q->front;
	//Output the queue's elements
	while (node != NULL){
		fprintf(out_channel, "%2u(%d)", node->page_number, node->reference);
		if (node != q->rear){
			fputs("-->", out_channel);
		}
		node = node->next;
	}
#endif	//End FIFO

	fputc('\n', out_channel);

	return;
}
