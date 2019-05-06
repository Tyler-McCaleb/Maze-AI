// Implementation for the linkedStackType class

#include "linkedStackType.h"
#include <vector>
using namespace std;


// funtion to overload the assignment operations
const linkedStackType & linkedStackType::operator=(const linkedStackType& otherStack)
{
	// if statement to avoid self copying
	if (this != &otherStack)
	{
		copyStack(otherStack);
	}

	return *this;
}


// FUnction to initialize the stack to an empty state.
void linkedStackType::initializeStack()
{
	// pointer to delete the node
	nodeType *temp;

	// while statement to handle while ther eare elements in the stack
	while (stackTop != nullptr)
	{
		// set temp to point to the current node
		temp = stackTop;

		// advance stackTop to the next node
		stackTop = stackTop->link;

		// deallocate memory occupied by temp
		delete temp;
	}
}


// FUnction to determine whether the stack is empty
bool linkedStackType::isEmptyStack() const
{
	// return true if the stackTop pointer is null
	return (stackTop == nullptr);
}


// Fucntion to determine wheter the stack is full
bool linkedStackType::isFullStack() const
{
	// A linked list stack can never be full
	return false;
}


// FUnction to add newItem to the stack
void linkedStackType::push(char& newItem, int row, int col, std::vector<int> rowsVisited, std::vector<int> colsVisited)
{
	// pointer to create the new node
	nodeType *newNode;

	// create the node
	newNode = new nodeType;

	// store newElement int he node
	newNode->state = newItem;
	newNode->rowLocation = row;
	newNode->colLocation = col;
	newNode->rowVisited = rowsVisited;
	newNode->colVisited = colsVisited;

	// insert new node before stackTop
	newNode->link = stackTop;

	//set stackTop to point to the top node
	stackTop = newNode;
}


//FUntion to return the top elemen of the stack
char linkedStackType::top()const
{
	assert(stackTop != nullptr);		// if stack is empty, terminate the program

	// return the top element
	return stackTop->state;
}

// function to return the row position of the node at the top of the stack
int linkedStackType::topRow()
{
	assert(stackTop != nullptr);		// if stack is empty, terminate

	// return the row stored in the top of the stack
	return stackTop->rowLocation;
}

// function to return the column position of the node at the top of the stack
int linkedStackType::topColumn()
{
	assert(stackTop != nullptr);		// if stack is empty, terminate

	// return the column stored in the top of the stack
	return stackTop->colLocation;


}

// function to return the rowsVisited vector from the top of the stack
vector<int> linkedStackType::returnTopVisitedRow()
{
	// if the stackis empty, terminate
	assert(stackTop != nullptr);

	// return the rowsVisited vector
	return stackTop->rowVisited;
}

// function to return the colsVisited vector from the top of the stack
vector<int> linkedStackType::returnTopColsVisited()
{
	// if the stack is empty, terminate
	assert(stackTop != nullptr);

	// return the colsVisited vector
	return stackTop->colVisited;
}


// Function to remove the top element of the stack
void linkedStackType::pop()
{
	// pointer to deallocate memory
	nodeType *temp;

	if (stackTop != nullptr)
	{
		// set temp to point to the top node
		temp = stackTop;

		// advance stackTop to the next node
		stackTop = stackTop->link;

		//delete the top node
		delete temp;
	}
	else
	{
		cout << "Cannot remove from an empty stack." << endl;
	}
}


// Default contructor
linkedStackType::linkedStackType()
{
	stackTop = nullptr;
}


// Copy contructor
linkedStackType::linkedStackType(const linkedStackType& otherStack)
{
	stackTop = nullptr;
	copyStack(otherStack);
}


// Destructor
linkedStackType::~linkedStackType()
{
	initializeStack();
}


// function to copy another stack
void linkedStackType::copyStack(const linkedStackType& otherStack)
{
	nodeType *newNode, *current, *last;

	// if stack is nonempty, make it empty
	if (stackTop != nullptr)
	{
		initializeStack();
	}

	if (otherStack.stackTop == nullptr)
	{
		stackTop = nullptr;
	}

	else
	{
		// set curren tot point to tehs tack to be copied.
		current = otherStack.stackTop;

		// copy the stackTop element of the stack
		stackTop = new nodeType;		// create the node

		// copy the info
		stackTop->state = current->state;

		// set the link field of the node to null
		stackTop->link = nullptr;

		// set last to point to the node
		last = stackTop;

		// set curren to point to the next node
		current = current->link;

		// copy the remaining stack
		while (current != nullptr)
		{
			newNode = new nodeType;

			newNode->state = current->state;
			newNode->link = nullptr;
			last->link = newNode;
			last = newNode;
			current = current->link;
		}
	}
}

// getter for the stackTop
nodeType* linkedStackType::getStackTop()
{
	return stackTop;
}
