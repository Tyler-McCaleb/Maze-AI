
// Header file for the linkedQueueType class

#ifndef LINKEDQUEUETYPE_H
#define LINKEDQUEUETYPE_H

#include <iostream>
#include <cassert>
#include <vector>

#include "queueParent.h"
#include "nodeType.h"

using namespace std;

class linkedQueueType : public queueParent
{
public:

	// Function to determin wheter the queue is empty
	bool isEmptyQueue() const;

	// functio to determine wheter the queue is full
	bool isFullQueue() const;

	// Function to iniitalize the queue to an empty state.
	void initializeQueue();

	// functio to return the first element of the queue
	char front() const;

	// function to return the last element of the queue
	char back() const;

	// function to add queueElement to the queue
	void addQueue(char& queueElement, int rowLocation, int colLocation, vector<int> rowsVisited, vector<int> colsVisited);

	// function to remove the first element of the queue
	void deleteQueue();

	// default constructor
	linkedQueueType();

	// destructor
	~linkedQueueType();

	// getter for the queueFront
	nodeType* getQueueFront();
	
	// getter for the queueRear pointer
	nodeType* getQueueRear();

	// function to return the row from the node in the front of the queue
	int returnFrontRow();

	// Function to return the column from the node in the front of the queue.
	int returnFrontCol();

	// Function to return the row visited vector in the node in the front of the queue
	vector<int> returnFrontRowVisited();

	// Function to return the column visited vecotr in the node in the front of 
	vector<int> returnFrontColVisited();

private:
	// pointer to the front of the queue
	nodeType *queueFront;

	// pointer to the rear of teh queue
	nodeType *queueRear;

};




#endif