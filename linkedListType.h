// Tyler McCaleb
// 2/17/2018
// Header File for a linked list
// Page 1119-1121 in 7th edition of book


#ifndef LINKEDLISTTYPE_H
#define LINKEDLISTTYPE_H

#include "nodeType.h"
#include "linkedListIterator.h"
#include <fstream>

//create the template class for a linked list
class linkedListType
{
public:
	
	// Function to overload the assignment operator
	const linkedListType& operator= (const linkedListType& otherList);
	

	// Function to initailize the list to an empty state.  This fucntion will result in head = nullptr, tail = nullptr, count = 0;
	void initializeList();

	// Function to determine whether the list is empty or not.  This function returns true if the list is empty, and false if it isn't
	bool isEmptyList() const;

	// Function to print the the data contained in the list.
	void print() const;

	// Fuction to return the number of nodes in the list (its length)
	int length() const;

	// Function to delete all the nodes in the list.  This function results in head and tail = null and count = 0
	void destroyList();

	// Function to return the first elemtn of the list.  
	// To call this function the list must exist and not be empty
	int front() const;

	// Function to return the last element of the list.  This list must exist and must not be empty
	int back() const;

	// Function to seach for a specific thing in the list.
	virtual bool search(const int & searchItem) const = 0;

	// Function to insert a new item at the beginning of the list.
	virtual void insertFirst(const int & newItem) = 0;

	// Function to insert a new item at the end of the list
	virtual void insertLast(const int & newItem) = 0;

	// Fucnito to delete a certain item in the list.
	virtual void deleteNode(const int & deleteItem) = 0;

	
	// Function to return an iterator at the beginning of the linked list.
	linkedListIterator begin();

	// Function to return an iterator one element past the last element of the linked list.
	linkedListIterator end();
	

	// Default constructor for a linked list
	linkedListType();

	//copy constructor
	linkedListType(const linkedListType& otherList);

	// Destructor of the linked list
	~linkedListType();

public:

	// Variable to store the number of elements in the list.
	int count; 

	//pointer to the first node of the list
	nodeType *first;

	// Pointer to the last node of the list
	nodeType *last;

private:
	// function to make a copy of otherList
	void copyList(const linkedListType& otherList);
};



#endif









