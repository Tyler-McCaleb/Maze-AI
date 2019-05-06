//Tyler McCaleb
// 3/1/2018
// Header file for a linkedListIterator
#ifndef LINKEDLISTITERATOR_H
#define LINKEDLISTITORATOR_H

#include "nodeType.h"


class linkedListIterator
{
public:
	//defulat contructor
	linkedListIterator();

	//contructor with a parameter
	linkedListIterator(nodeType *ptr);

	// function to overload the dereferencing operator (*)
	int operator*();

	// function to over load the pre-increment operator
	linkedListIterator operator++();

	// functino o overload the equality operator
	bool operator==(const linkedListIterator& right) const;

	// function to overload the not equal to operator
	bool operator!=(const linkedListIterator& right) const;

private:

	// pointer to point to the current node in the linked list
	nodeType *current;
};


#endif




