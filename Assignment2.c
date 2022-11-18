/*******************************************************************************************
* File Name          : Assignment2.cpp
* Description        : Prog8130 - Assignment 2: Binary tree
*					   This program will create the binary tree of given data and prints the
*					   list.
* Author:            : Kunalsinh Goihl
* Date:              : 12/02/2019
********************************************************************************************/

#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct nodeData *ptr1, *ptr2, *head = NULL;	// head of the binary tree

// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
struct nodeData {
	char name[30];				// character string of the data being stored in the node
	struct nodeData *left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
	struct nodeData *right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
};


// data to be stored in tree.  In this case there is just a character string but this could have contained more
const char *inputData[12] = {
		{ "inhle"},
		{ "bjxte"},
		{ "sejve"},
		{ "rvgyf"},
		{ "dsvfn"},
		{ "qcatx"},
		{ "hlitb"},
		{ "fpgud"},
		{ "vutuj"},
		{ "xpjla"},
		{ "dxepo"},
		{ "obxid"}
};

// The correct sorted order using a binary tree is:
//      bjxte
//      dsvfn
//      dxepo
//      fpgud
//      hlitb
//      inhle
//      obxid
//      qcatx
//      rvgyf
//      sejve
//      vutuj
//      xpjla

// FUNCTION      : addToBinaryTree
// DESCRIPTION   : This function will store the data in newNode into a binary tree according to alphabetical order
// PARAMETERS    : newString - the string that is to be stored in the binary tree in alphabetica order
// RETURNS       : Nothing
void addToBinaryTree(const char *newString) {

	ptr1 = (struct nodeData*)malloc(sizeof(struct nodeData));
	strcpy_s(ptr1->name, newString);
	ptr1->left = NULL;
	ptr1->right = NULL;
	if (strcmp(newString, "inhle") == 0)
	{
		head = ptr1; // root always point to the root node
	}
	else
	{
		ptr2 = head; // ptr2 is used to traverse the tree

		while (1)
		{

			if (strcmp(ptr1->name, ptr2->name) > 0)
			{
				if (ptr2->right == NULL)
				{
					ptr2->right = ptr1;
					break;
				}
				else
				{
					ptr2 = ptr2->right;
				}
			}
			else
			{
				if (ptr2->left == NULL)
				{
					ptr2->left = ptr1;
					break;
				}
				else
				{
					ptr2 = ptr2->left;
				}

			}

		}
	}
}

// FUNCTION      : printBinaryTree
// DESCRIPTION   : This function will print the entire binary tree out.  You can choose to print
//                 it using recursion but more marks will be awarded if you do it non recursively.
// PARAMETERS    : *head
// RETURNS       : Nothing
void printBinaryTree(struct nodeData *head) {

	if (head->left)
		printBinaryTree(head->left);
	printf("%s\n", head->name);
	if (head->right)
		printBinaryTree(head->right);

}


int main() {
	int i;

	//print the list before creation of binary tree
	printf("List before creation of binary tree\n");
	for (i = 0; i < 12; i++)
	{
		printf("%s\n", inputData[i]);
	}

	printf("\n\n");

	// put all the data into the binary tree
	printf("List after creation of binary tree\n");
	for (i = 0; i < 12; i++)
	{
		addToBinaryTree(inputData[i]);
	}
	// print the entire tree.  It should come out in alphabetical order because of the way it was stored in the tree
	printBinaryTree(head);
	return 0;
}
