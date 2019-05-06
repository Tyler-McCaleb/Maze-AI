//Tyler McCaleb
// 9/22/2018
// Header file for the nodeType struct


#ifndef NODETYPE_H
#define NODETYPE_H

#include <vector>


// Definition of the node
struct nodeType
{
	// Tells if the node is the entrance, the exit, a wall, or a path
	char state;

	// ints to hold the position of the node in the maze
	int rowLocation = 0;
	int colLocation = 0;

	// links to facilitate the queue
	nodeType *link = nullptr;

public:
	// Vector to hold the rows visited to get to this point
	std::vector<int> rowVisited;

	// Vector to hold the columns visited to get to this point
	std::vector<int> colVisited;
};

#endif
