#ifndef  LINKEDSTACKTYPE_H
#define LINKEDSTACKTYPE_H

#include <iostream>
#include <cassert>
#include <vector>
#include "stackParent.h"
#include "nodeType.h"

using namespace std;

class linkedStackType : public stackParent
{
public:
	
	// funtion to overload the assignment operations
	const linkedStackType & operator=(const linkedStackType& otherStack);

	// FUnction to initialize the stack to an empty state.
	void initializeStack();

	// FUnction to determine whether the stack is empty
	bool isEmptyStack() const;

	// Fucntion to determine wheter the stack is full
	bool isFullStack() const;

	// FUnction to add newItem to the stack
	void push(char& newItem, int row, int col, std::vector<int> rowsVisited, std::vector<int> colsVisited);

	//FUntion to return the top elemen of the stack
	char top()const;

	// Function to remove the top element of the stack
	void pop();

	// Default contructor
	linkedStackType();

	// Copy contructor
	linkedStackType(const linkedStackType& otherStack);

	// Destructor
	~linkedStackType();

	// function to return the row position of the node at the top of the stack
	int topRow();

	// function to return the column position of the node at the top of the stack
	int topColumn();

	// getter for the stackTop
	nodeType* getStackTop();

	// function to return the colsVisited vector from the top of the stack
	vector<int> returnTopColsVisited();

	// function to return the rowsVisited vector from the top of the stack
	vector<int> returnTopVisitedRow();



private:

	nodeType * stackTop; // pointer to the stack

	// function to copy another stack
	void copyStack(const linkedStackType& otherStack);
};

#endif // ! LINKEDSTACKTYPE_H
