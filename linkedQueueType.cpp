// Implementation file for the linkedQueueType class

#include "linkedQueueType.h"
#include <vector>

using namespace std;

// Function to determine whether the queue is empty
bool linkedQueueType::isEmptyQueue() const
{
	return (queueFront == nullptr);
}


// functio to determine wheter the queue is full
bool linkedQueueType::isFullQueue() const
{
	// A linked list cannot ever be full
	return false;
}


// Function to iniitalize the queue to an empty state.
void linkedQueueType::initializeQueue()
{
	nodeType *temp;

	// while there are elements left in the queue
	while (queueFront != nullptr)
	{
		// set temp to point to the current node
		temp = queueFront;

		// advance first to the next node
		queueFront = queueFront->link;

		// deallocate memory occupied by temp
		delete temp;

	}

	// set rear to nullptr
	queueRear = nullptr;
}


// functio to return the first element of the queue
char linkedQueueType::front() const
{
	// terminate if the queue is empty
	//assert(queueFront != nullptr);

	return queueFront->state;
}

// Function to return the row visited vector in the node in the front of the queue
vector<int> linkedQueueType::returnFrontRowVisited()
{
	return queueFront->rowVisited;
}

// Function to return the column visited vecotr in the node in the front of 
vector<int> linkedQueueType::returnFrontColVisited()
{
	return queueFront->colVisited;
}



// function to return the last element of the queue
char linkedQueueType::back() const
{
	// terminate if the queue is empty
	//assert(queueFront != nullptr);

	return queueRear->state;
}


// function to add queueElement to the queue
void linkedQueueType::addQueue(char& queueElement, int rowLocation, int colLocation, vector<int> rowsVisited, vector<int> colsVisited)
{
	nodeType * newNode;

	// create the node
	newNode = new nodeType;

	// store the info
	newNode->state = queueElement;
	newNode->rowLocation = rowLocation;
	newNode->colLocation = colLocation;
	newNode->rowVisited = rowsVisited;
	newNode->colVisited = colsVisited;

	// initialize the link field to nullptr
	newNode->link = nullptr;

	// if initially the que eis empty
	if (queueFront == nullptr)
	{
		queueFront = newNode;
		queueRear = newNode;
	}
	else
	{
		queueRear->link = newNode;
		queueRear = queueRear->link;
	}

}


// function to remove the first element of the queue
void linkedQueueType::deleteQueue()
{
	nodeType *temp;

	if (!isEmptyQueue())
	{
		// make temp point to the first node
		temp = queueFront;

		// adcance queueFront
		queueFront = queueFront->link;

		// delete teh frist ndoe
		delete temp;

		// if after delete teh queue is empty
		if (queueFront == nullptr)
		{
			// set queue rear to nullptr
			queueRear = nullptr;
		}
	}
}


// default constructor
linkedQueueType::linkedQueueType()
{
	// set fron tto null
	queueFront = nullptr;

	// set rear to null
	queueRear = nullptr;
}


// destructor
linkedQueueType::~linkedQueueType()
{
	// call the initialize queue function
	initializeQueue();
}

// getter for the queueFront
nodeType* linkedQueueType::getQueueFront()
{
	return queueFront;
}

// getter for the queueRear pointer
nodeType* linkedQueueType::getQueueRear()
{
	return queueRear;
}


// function to return the row from the node in the front of the queue
int linkedQueueType::returnFrontRow()
{
	return queueFront->rowLocation;
}

// Function to return the column from the node in the front of the queue.
int linkedQueueType::returnFrontCol()
{
	return queueFront->colLocation;
}

