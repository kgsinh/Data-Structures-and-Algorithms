/*******************************************************************************************
* File Name          : Assignment1.cpp
* Description        : Prog8130 - Assignment 1: Linked Lists
*					   This program uses linked lists to hold and print a list of words
*					   organized by index number assosciated with each word. Each word can
*					   consist of maximum 30 characters.
*
* Author:            : Kunalsinh Gohil
* Date:              : 06/02/2019
********************************************************************************************/

/*********HeaderFiles***********/
#include "pch.h"
#include <stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include <string.h>

/*************MacroDefinition*****************/
#define NUMBER_OF_DATA_ITEMS   10  // the number of data items to be used in list

/*********GLobalVariableDeclaration***********/
int count = 0;
struct LinkedListNode *temp, *pointer1, *newNode;

// structure/typedef used for holding data
typedef struct {
	char name[30];
	int index;
} inputData;

// definition of linked list data nodes
typedef struct LinkedListNode {
	struct LinkedListNode		*ptrNextNode;		// pointer to next node in list (NULL if the end)
	char						NameData[30];		// the name to be stored (no need to store index)
} LinkedListNodeDef;

// prototypes
LinkedListNodeDef *AddToLinkedList(LinkedListNodeDef *ptrHead, char *NameData, int DataIndex);
void PrintLinkedList(LinkedListNodeDef *ptrHead);

// make the data positions the last 5 digits of student number
// for example if my student number ended in 94330 the data will be as supplied

// data used for test
// paste the data here that was created by Prog8130Assign1DataCreator.exe
inputData iData[10] = {
	{ "fish", 1 },
	{ "pickels", 2 },
	{ "orange", 4 },
	{ "butter", 8 },
	{ "allan", 7 },
	{ "water", 8 },
	{ "snake", 8 },
	{ "car", 9 },
	{ "kiwi", 7 },
	{ "candy", 3 }
};

/*Correct order after inserting into list is:
1. fish
2. pickels
3. candy
4. orange
5. butter
6. allan
7. water
8. kiwi
9. snake
10. car */


int main(void) {
	int i;

	// define linked list head
	struct LinkedListNode		*ptrHead = NULL;

	// Print out the input data
	printf("Data before Linked List is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
	{
		printf("%s , %d\n", iData[i].name, iData[i].index);
	}
	printf("\n");
	// insert the data into Linked List
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
	{
		ptrHead = AddToLinkedList(ptrHead, iData[i].name, iData[i].index);
	}

	// now print out the list in order it is stored starting at head
	PrintLinkedList(ptrHead);
	return 0;
}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
//		           int DataIndex				- Index of data
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef *AddToLinkedList(LinkedListNodeDef *ptrHead, char *NameData, int DataIndex) {
	// put code in here to add the item(s) to the linked list

	if (DataIndex >= count)
	{
		temp = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
		strcpy_s(temp->NameData, NameData);
		temp->ptrNextNode = NULL;

		// find the end of list
		pointer1 = ptrHead;
		if (pointer1 != NULL)
		{
			while (pointer1->ptrNextNode != NULL)
			{
				pointer1 = pointer1->ptrNextNode;
			}
			pointer1->ptrNextNode = temp;

		}
		else
			ptrHead = temp;
		count++;
	}
	else
	{
		temp = ptrHead;
		for (int j = 1; j < DataIndex - 1; j++)
		{
			temp = temp->ptrNextNode;
		}
		newNode = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
		strcpy_s(newNode->NameData, NameData);
		newNode->ptrNextNode = NULL;
		newNode->ptrNextNode = temp->ptrNextNode;
		temp->ptrNextNode = newNode;
		count++;
	}
	return ptrHead;

}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//				   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef *ptrHead) {
	// put code in here to print the linked list out
	struct LinkedListNode *temp;

	temp = ptrHead;
	if (temp == NULL)
	{
		printf("No List\n");
	}
	else
	{
		printf("Priortized Linked List\n");
		while (temp != NULL)
		{
			for (int k = 1; k <= 10; k++)
			{
				printf("%d.%s\n", k, temp->NameData);
				temp = temp->ptrNextNode;
			}
		}
	}

}
/******End of Program******/
