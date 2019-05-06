// Implementation file for linkedListType.h
// Tyler McCaleb
// 3/10/18


#include <iostream>
#include "linkedListType.h"
#include <assert.h>
#include <fstream>

using namespace std;


// Function to determine if the class is empty
bool linkedListType::isEmptyList() const
{
	return (first == nullptr);
}

// Default constructor for a linked list
linkedListType::linkedListType()
{
	first = nullptr;
	last = nullptr;
	count = 0;
}

// FUnctino to destroy the list
void linkedListType::destroyList()
{
	// pointer to deallocate the memeory occupied by the node.
	nodeType *temp;

	// While loop to loop while there are nodes in the list
	while (first != nullptr)
	{
		// set temp to current node
		temp = first;

		// advance first to the next node
		first = first->link;

		// Delete the temporary 
		delete temp;
	}

	// initailzie last to nullptr
	last = nullptr;

	// reset count
	count = 0;
}

// function to print the list
void linkedListType::print() const
{
	// pointer to traverse the list
	nodeType *current;

	// set curren so that it points to the first node
	current = first;

	// while more data to print
	while (current != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << current->info << " \t";
				current = current->link;
			}

			cout << endl;
		}
	}
}


// function to return the length of a list
int linkedListType::length() const
{
	return count;
}

// Function to return the data of the first node.
int linkedListType::front() const
{
	// stop if there is no list
	assert(first != nullptr);

	// reutrn the infor from the first node.
	return first->info;
}

// function to return the data form the last node.
int linkedListType::back() const
{
	// stop if the list is empty
	assert(first != nullptr);

	// Return the infor of the last node
	return last->info;
}


// Fucntion that returns an iterator at the be beginning of the list
linkedListIterator linkedListType::begin()
{
linkedListIterator temp;

return temp;
}

// Function that returns an iterator at the end of the list.
linkedListIterator linkedListType::end()
{
linkedListIterator temp(nullptr);

return temp;
}



// function to copy the list
void linkedListType::copyList(const linkedListType& otherList)
{
	// pointer to create a node
	nodeType *newNode;

	// pointer to travrser the list
	nodeType *current;

	// if statement to make the list empty if it is not empty
	if (first != nullptr)
	{
		destroyList();
	}

	//if statement to andle once the list is empty
	if (otherList.first == nullptr)
	{
		first = nullptr;
		last = nullptr;
		count = 0;
	}

	else
	{
		// sets current pointer to the list to be copied
		current = otherList.first;
		count = otherList.count;

		// copy the first node
		// create the node
		first = new nodeType;

		//copy the info
		first->info = current->info;
		first->link = nullptr;

		// make the last point equal to the first node
		last = first;

		// make current point tot he next node
		current = current->link;

		// copy the ramaining list
		while (current != nullptr)
		{
			// create a node
			newNode = new nodeType;

			// copy the info
			newNode->info = current->info;

			// set the link of newNOde to nullptr
			newNode->link = nullptr;

			// attach newNode after last
			last->link = newNode;

			//make last point to the actual last node
			last = newNode;

			// make current point to the next node
			current = current->link;
		}
	}
}

// Destructor for the linkedListType
linkedListType::~linkedListType()
{
	destroyList();
}

//Copy Constructor
linkedListType::linkedListType(const linkedListType &otherList)
{
	first = nullptr;

	// call the copy list function
	copyList(otherList);
}


//Overload the Assignment Operator
const linkedListType& linkedListType::operator= (const linkedListType& otherList)
{
	//if statement to avoid copying itself
	if (this != &otherList)
	{
		// call the copy list function
		copyList(otherList);
	}

	return *this;
}



//Function to initailize a list
void linkedListType::initializeList()
{
	// call the destory list function to delete any nodes in the list
	destroyList();
}


