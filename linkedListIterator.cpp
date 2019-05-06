// Implementation file for linkedListIterator.h
// Tyler McCaleb
// 3/10/18

#include "linkedListIterator.h"

using namespace std;

//defulat contructor
linkedListIterator::linkedListIterator()
{
	current = nullptr;
}

//contructor with a parameter
linkedListIterator::linkedListIterator(nodeType *ptr)
{
	current = ptr;
}

// function to overload the dereferencing operator (*)
int linkedListIterator::operator*()
{
	return current->state;
}

// function to over load the post-increment operator
linkedListIterator linkedListIterator::operator++()
{
	current = current->link;
	return *this;
}

// functino o overload the equality operator
bool linkedListIterator::operator==(const linkedListIterator& right) const
{
	return (current == right.current);
}

// function to overload the not equal to operator
bool linkedListIterator::operator !=(const linkedListIterator& right) const
{
	return (current != right.current);
}
