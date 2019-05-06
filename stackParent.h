// Header file for the abstract class stackADT

#ifndef STACKPARENT_H
#define STACKPARENT_H

#include <vector>

class stackParent
{
public:
	// Function to initialize the stack to an empty state
	virtual void initializeStack() = 0;

	// Function to determine whetere the stack is empty or not
	virtual bool isEmptyStack() const = 0;

	// Funtion to determine if the stack is full
	virtual bool isFullStack() const = 0;

	// Function to add newItem to the stack
	virtual void push(char& newItem, int row, int col, std::vector<int> rowVisited, std::vector<int> colVisited) = 0;

	// FUntion to returne the top element of the stack
	virtual char top() const = 0;

	// Function to remove the top element of the stack
	virtual void pop() = 0;
};



#endif
