/*******************************************************************************
* File Name          : circularQueueFix.cpp
* Description        : Circular Queue Final skeleton starting point
*
* Author             : Kunalsinh Gohil
* Date               : April 12, 2019
******************************************************************************
*/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI myReadThreadFunction(LPVOID lpParam);                             // function used by read from queue thread
unsigned int putToTheQueue(char *ptrInputBuffer, unsigned int bufferLength);    // circular queue function to add data to queue
unsigned int getFromTheQueue(char *ptrOutputBuffer, unsigned int bufferLength); // circular queue function to remove data from queue
int checkIfVowel(char characterToCheck);                                        // function that checks if char is a vowel

#define BUFFER_SIZE         200                // local buffer used for sending or receiving data to/from queue in main and worker thread

#define INPUT_TIMEOUT_MS    2000               // dequeue every 2 seconds

#define CIRCULAR_QUEUE_SIZE 10                 // size of the circular queue

																				// data used to keep track of circular queue (DO NOT CHANGE THESE DATA ITEMS)

char qBuffer[CIRCULAR_QUEUE_SIZE] = { 0 }; // circular queue buffer (note this is different than what you did in class)
volatile int queueCount = 0;               // number of characters currently in cirucular queue
volatile int indexHead = NULL;             // index into qBuffer of location where data is added to queue
volatile int indexTail = NULL;             // index into qBuffer of location where data is removed from queue

										   // note an index is different than a pointer like used in assignment 3.  For an index you can access the data like so:
										   //  qBuffer[indexHead]  instead of using a pointer.  This type of circular queue implementation is pretty commonly described
										   // on the internet but you will have to adapt it to this skelleton.


										   // DO NOT CHANGE THE CODE IN MAIN
int main()
{
	HANDLE  hThread;            // handle to thread
	char    inputBuffer[BUFFER_SIZE];

	indexHead = indexTail = 0;  // set indexes to start of buffer

								// create a thread that will consume the data we type in to demonstrate dequeing the data
	hThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		myReadThreadFunction,   // thread function name
		NULL,                   // argument to thread function (not being used)
		0,                      // use default creation flags 
		NULL);                  // returns the thread identifier (not being used)

								// get a string from the console and queue it to circular queue
	while (1)
	{
		scanf_s("%s", inputBuffer, BUFFER_SIZE);    // get data from console

													// put the data into the circular queue but check if an error (marked by queue function returning 0) occurred
		if (putToTheQueue(inputBuffer, (unsigned int)strlen(inputBuffer)) == 0)
			printf("Error queuing data\n");
	}
	return 0;
}

// FUNCTION      : putToTheQueue
// DESCRIPTION   :
//   Put the supplied data into a circular queue
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the queue
//   bufferLength   - how many characters are in the buffer being put into the queue
//
// RETURNS       :
//   Number of characters successfully queued

unsigned int putToTheQueue(char *ptrInputBuffer, unsigned int bufferLength)
{
	unsigned int numberOfCharsQueued = 0;  // number of characters placed in circular queue

	indexHead = indexTail = -1;
										   
	while (numberOfCharsQueued < bufferLength)
	{
		int i = 0;
		char input = *(ptrInputBuffer + numberOfCharsQueued);//read a character from the input stream

		if ((indexTail == CIRCULAR_QUEUE_SIZE - 1 && indexHead == 0) || (indexTail + 1 == indexHead))// check if queue is full
			break;

		if (indexTail == CIRCULAR_QUEUE_SIZE - 1)// if tail is at last element, then shift it to first element
			indexTail = 0;
		

		if (indexHead == -1)
			indexHead = 0;
		
		qBuffer[i] = input; //insert value	
		i++;    //increment i
		indexTail++;//move tail one ahead
		numberOfCharsQueued++;//increase number of characters queued by 1
		queueCount++;//increase queue count by 1
	}


	return numberOfCharsQueued;
}

// FUNCTION      : getFromTheQueue
// DESCRIPTION   :
//   Read as much data as there is room for from the circular queue
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from queue
//   bufferLength    - maxiumum number of characters that can be read (IE the size of the output buffer)
//
// RETURNS       :
//   Number of characters successfully queued (0 if none are read)

unsigned int getFromTheQueue(char *ptrOutputBuffer, unsigned int bufferLength)
{
	unsigned int readCount = 0;

	while (readCount < bufferLength)
	{
		if (indexTail == indexHead)//check if queue if empty, ie, when tail is equal to head
			break;

		*(ptrOutputBuffer + readCount) = indexHead;//get element from the queue

		if (indexHead == (CIRCULAR_QUEUE_SIZE - 1))//if head is at last element, then shift it to the beginning
		{
			indexHead = 0;
		}

		readCount++;//increase counter of dequeued elements
		queueCount--;//decrease counter of elements in queue
		indexHead++;//move head to the next element in queue
	}

	*(ptrOutputBuffer + readCount) = '\0';//null characted to ensure output pointer is terminated

	return readCount;
}

// FUNCTION      : checkIfVowel
// DESCRIPTION   :
//   This function will check a given character to see if it is a vowel
// PARAMETERS    :
//   characterToCheck - a character to check for vowel
//
// RETURNS       :
//   0 if not a vowel / non zero if it is a vowel

int checkIfVowel(char characterToCheck)
{
	int itIsAVowel = 0;
	
	// add code to check if the characterToCheck is a vowel or not
	//condition for vowel
	if (characterToCheck == 'a' || characterToCheck == 'e' || characterToCheck == 'i' || characterToCheck == 'o' || characterToCheck == 'u' ||
		characterToCheck == 'A' || characterToCheck == 'E' || characterToCheck == 'I' || characterToCheck == 'O' || characterToCheck == 'U')
		printf("Hi\n");
		return itIsAVowel;
	
}

// FUNCTION      : myReadThreadFunction
// DESCRIPTION   :
//   A seperate thread from the main program that will independently check for data in queue and print it out
//   DO NOT CHANGE THIS CODE!
// PARAMETERS    :
//   lpParam - arguement passed into thread (not used in this example)
//
// RETURNS       :
//   Will never return so no effective return value

// DO NOT CHANGE THE CODE IN myReadThreadFunction

DWORD WINAPI myReadThreadFunction(LPVOID lpParam)
{
	char readBuffer[BUFFER_SIZE];     // local buffer to put the data into when reading from queue and print
	unsigned int  readCount = 0;      // the number of characters read from queue

	while (1)
	{
		Sleep(INPUT_TIMEOUT_MS);      // wait for some data to be received

									  // check if data is available and if so print it out
		readCount = getFromTheQueue(readBuffer, 1);   // note this will read each character out one at a time

		if (checkIfVowel(*readBuffer) != 0)
			printf("UNQUEUE: %c %s\n", *readBuffer, "VOWEL");
		else
			printf("UNQUEUE: %c %s\n", *readBuffer, "NOT VOWEL");

	}
	return 0;    // will never reach here
}

// end code *     *   
