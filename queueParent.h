// Header file for the queueADT class

#ifndef QUEUEPARENT_H
#define QUEUEPARENT_H

#include <vector>

class queueParent
{
public:

	// function to determine whether the queue is empty
	virtual bool isEmptyQueue() const = 0;

	// function to determine whether th queue is full
	virtual bool isFullQueue() const = 0;

	// function to initialzie the queue to an empty state
	virtual void initializeQueue() = 0;

	// function to return the first element of the queue.
	virtual char front() const = 0;

	// function to return the last element of the queue.
	virtual char back() const = 0;

	// Function to add queueElement ot the queue.
	virtual void addQueue(char& queueElement, int rowLocation, int colLocation, std::vector<int> rowsVisited, std::vector<int> colsVisited) = 0;

	// Function to remove the first element of the queue.
	virtual void deleteQueue() = 0;

};

#endif
