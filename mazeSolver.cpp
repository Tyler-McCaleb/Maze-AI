// Tyler McCaleb
// September 22, 2018
/*
	This program will read in a 10 x 10 maze from a text file into an array.  The array will contain "W" to signify a wall, "P" to signify a path, "E" to signify the entranct, and a "X" to signify the exit from the
	maze.  The program will perform both a breadth first search and a depth first search to travel from the entrace of the maze to the end.
*/

#include <iostream>
#include <fstream>
#include "nodeType.h"
#include "linkedQueueType.h"
#include "linkedStackType.h"
#include <vector>


using namespace std;

// Function Prototypes
// Function to read the maze into the array
void createMaze(char mazeArrayP[10][10]);

// Function to search for the entrace of the maze
void findEntrance(int &entranceRowP, int &entranceColP, char mazeArray[10][10]);

// Function to give the entrance node it's data.
void createEntrance(nodeType &entraceToMazeP, int row, int col, char mazeArray[10][10]);

// function to print the maze
void printMaze(char maze[10][10]);

// function to print every node that was explored
void printEntirePath(int maze[10][10], char mazeArray[10][10], std::vector<int> rowsVisited, std::vector<int> colsVisited);

// function to print the path from the entrance to the exit.
void printPath(int maze[10][10], char mazeArray[10][10], std::vector<int> rowsVisited, std::vector<int> colsVisited, int exitRow, int exitCol);

// Function to find the path using a depth first search
void breadthFirstSearch(char mazeArray[10][10], int entranceRow, int entranceCol);

// Function to find the path using a depth first search
void depthFirstSearch(char mazeArray[10][10], int entranceRow, int entranceCol);

// Function to perform the Breadth First Search
void breadthFirstExploration(char mazeArray[10][10], int entranceRow, int entranceCol);

// Function to perform the Breadth First Search
void depthFirstExploration(char mazeArray[10][10], int entranceRow, int entranceCol);

// FUnction to determine if a node is the exit or not
bool evaluateNode(char currentNode);

// Function to evaluate the vectors
bool visited(int i, int j, std::vector<int>rowsVisited, std::vector<int> colsVisited);


int main()
{
	// Declare variables
	char mazeArray[10][10];						// array to hold the maze
	int entranceRow = 0;						// int to hold the row that the entrance is on
	int entranceCol = 0;						// int to hold the column that the entrace is on
	nodeType entranceToMaze;					// Node to hold the entrace to the maze.


	// Call the create maze function
	createMaze(mazeArray);


	// Call the search for entrance function to assing the values to entraceRow and entranceCol
	findEntrance(entranceRow, entranceCol, mazeArray);

	// Create the initial node from the entrance 
	createEntrance(entranceToMaze, entranceRow, entranceCol, mazeArray);

	// Print the original maze to the console
	cout << "This is the maze that is being searched through:" << endl;
	printMaze(mazeArray);

	// Search for the path through the maze using a breadth first search (queue)
	breadthFirstSearch(mazeArray, entranceRow, entranceCol);

	// Explore the maze by using breadth search (queue)
	breadthFirstExploration(mazeArray, entranceRow, entranceCol);

	// Search Through the maze using a dpeth first search (stack)
	depthFirstSearch(mazeArray, entranceRow, entranceCol);

	// Explore the maze by using a depth first search (stack)
	depthFirstExploration(mazeArray, entranceRow, entranceCol);
	
	cout << "Press any key to exit." << endl;
	cin.get();

	return 0;
}



// Function Definitions
// Function to read the maze into the array
void createMaze(char mazeArrayP[10][10])
{
	// Declare an input stream
	ifstream input;

	// Open the file
	input.open("maze.txt");

	// check to make sure that the input file opened
	if (!input)
	{
		cout << "The file could not be opened." << endl;
		return;
	}

	// read the information from the file into the array
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			input >> mazeArrayP[i][j];
		}
	}

	// close the input file
	input.close();

	return;
}

// Function to search for the entrace of the maze
void findEntrance(int &entranceRowP, int &entranceColP, char mazeArray[10][10])
{
	// for loop to move through the maze array and make sure that all characters are upper case
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mazeArray[i][j] = toupper(mazeArray[i][j]);
		}
	}

	// for loop to move through the maze array to find the E that signifies the entrance
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// If statement to change the values of the entraceRow and Column to the current i and j when the E is found
			if (mazeArray[i][j] == 'E')
			{
				entranceRowP = i;
				entranceColP = j;
				return;
			}
		}
	}

	// Print a messag if the entrace is never dound
	cout << "The entrace could not be found" << endl;
}

// Function to give the entrance node it's data.
void createEntrance(nodeType &entranceToMazeP, int row, int col, char mazeArray[10][10])
{
	// assign the data to the entrace node
	entranceToMazeP.rowLocation = row;
	entranceToMazeP.colLocation = col;
	entranceToMazeP.state = mazeArray[row][col];
}


// function to print the maze
void printMaze(char maze[10][10])
{
	cout << "\n" << endl;
	// for loop to move through the maze and print each element in a readable way
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << maze[i][j] << "\t";
		}

		cout << "\n";
	}

	cout << "_________________________________________________________________________\n\n" << endl;
}


// function to print the path
void printEntirePath(int maze[10][10], char mazeArray[10][10], vector<int> rowsVisited, vector<int> colsVisited)
{
	cout << "\n" << endl;
	// for loop to move through the maze and print each element in a readable way
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// if statement to print the step number that was taken if the area was a path
			if (maze[i][j] > 0)
			{
				cout << maze[i][j] << "\t";
			}

			// else statemen to print the walls
			else
			{
				cout << mazeArray[i][j] << "\t";
			}
		}

		cout << "\n";
	}

	cout << "_________________________________________________________________________" << endl;
}


// Function to find the path using a depth first search
void breadthFirstSearch(char mazeArray[10][10], int entranceRow, int entranceCol)
{
	// Create your queue
	linkedQueueType mazeQueue;

	// Pointer to create new nodes
	nodeType *temp;

	// Declare variables
	bool exitFound = false;					// variable to hold if the exit has been found or not
	int count = 1;							// Variable to hold how many steps the agent has taken to get to this point
	bool visited[10][10] = { 0 };			// Array to hold which nodes that have already been visited
	int pathThroughMaze[10][10] = { 0 };	// Array to hold the path taken through the maze
	int sizeOfRowsVisited = 0;				// size of the vector of rows
	int sizeOfColsVisited = 0;				// size of the vector of columns

	// Vectors to create the first node
	vector<int> tempRowVector;
	vector<int> tempColVector;

	// Add the entrace to the vectors
	tempRowVector.push_back(entranceRow);
	tempColVector.push_back(entranceCol);


	// Add the entrace node to the queue
	mazeQueue.addQueue(mazeArray[entranceRow][entranceCol], entranceRow, entranceCol, tempRowVector, tempColVector);

	while (!exitFound)
	{
		// Evaluate the first node in the queue to see if it is the exit
		if (evaluateNode(mazeQueue.front()))
		{
			exitFound = true;

			// Add the exit node to the path vectors
			mazeQueue.returnFrontRowVisited().push_back(mazeQueue.returnFrontRow());
			mazeQueue.returnFrontColVisited().push_back(mazeQueue.returnFrontCol());


			// print the path through the maze after the breadth first search
			cout << "\nThis is the path through the maze discovered by the breadth first search" << endl;
			printPath(pathThroughMaze, mazeArray, mazeQueue.returnFrontRowVisited(), mazeQueue.returnFrontColVisited(), mazeQueue.getQueueFront()->rowLocation, mazeQueue.getQueueFront()->colLocation);

			cout << "\n" << endl;

			// destroy the queue
			mazeQueue.~linkedQueueType();

			return;

		}

		// else statement move on from the current node.
		if (exitFound != true && visited[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol()] != true)
		{

			// Check north of the current node to find a path
			if ((mazeQueue.returnFrontRow() - 1 >= 0) && visited[mazeQueue.returnFrontRow() - 1][mazeQueue.returnFrontCol()] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = mazeQueue.returnFrontRow() - 1;
				temp->colLocation = mazeQueue.returnFrontCol();
				temp->state = mazeArray[mazeQueue.returnFrontRow() - 1][mazeQueue.returnFrontCol()];


				// Add the new node's path to this node
				for (int i = 0; i < mazeQueue.returnFrontRowVisited().size(); i++)	// add the rows
				{
					temp->rowVisited.push_back(mazeQueue.returnFrontRowVisited()[i]);
				}

				for (int i = 0; i < mazeQueue.returnFrontColVisited().size(); i++)	// add the columns
				{
					temp->colVisited.push_back(mazeQueue.returnFrontColVisited()[i]);
				}

				// Add the current node to the back of the path
				temp->rowVisited.push_back(mazeQueue.returnFrontRow());
				temp->colVisited.push_back(mazeQueue.returnFrontCol());

				// if statement to add a path or the exit to the queue.
				if (mazeArray[mazeQueue.returnFrontRow() - 1][mazeQueue.returnFrontCol()] == 'P' || mazeArray[mazeQueue.returnFrontRow() - 1][mazeQueue.returnFrontCol()] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					mazeQueue.addQueue(temp->state, temp->rowLocation, temp->colLocation, temp->rowVisited, temp->colVisited);
				}

				// delete temp
				delete temp;
			}

			// Check east of the current node to find a path
			if ((mazeQueue.returnFrontCol() + 1 < 10) && visited[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() + 1] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = mazeQueue.returnFrontRow();
				temp->colLocation = mazeQueue.returnFrontCol() + 1;
				temp->state = mazeArray[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() + 1];


				// Add the new node's path to this node
				for (int i = 0; i < mazeQueue.returnFrontRowVisited().size(); i++)	// add the rows
				{
					temp->rowVisited.push_back(mazeQueue.returnFrontRowVisited()[i]);
				}

				for (int i = 0; i < mazeQueue.returnFrontColVisited().size(); i++)	// add the columns
				{
					temp->colVisited.push_back(mazeQueue.returnFrontColVisited()[i]);
				}

				// Add the current node to the back of the path
				temp->rowVisited.push_back(mazeQueue.returnFrontRow());
				temp->colVisited.push_back(mazeQueue.returnFrontCol());

				// if statement to add a path or the exit to the queue.
				if (mazeArray[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() + 1] == 'P' || mazeArray[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() + 1] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					mazeQueue.addQueue(temp->state, temp->rowLocation, temp->colLocation, temp->rowVisited, temp->colVisited);
				}

				// delete temp
				delete temp;

			}


			// Check south of the current node to find a path
			if ((mazeQueue.returnFrontRow() + 1 < 10) && visited[mazeQueue.returnFrontRow() + 1][mazeQueue.returnFrontCol()] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = mazeQueue.returnFrontRow() + 1;
				temp->colLocation = mazeQueue.returnFrontCol();
				temp->state = mazeArray[mazeQueue.returnFrontRow() + 1][mazeQueue.returnFrontCol()];


				// Add the new node's path to this node
				for (int i = 0; i < mazeQueue.returnFrontRowVisited().size(); i++)	// add the rows
				{
					temp->rowVisited.push_back(mazeQueue.returnFrontRowVisited()[i]);
				}

				for (int i = 0; i < mazeQueue.returnFrontRowVisited().size(); i++)	// add the columns
				{
					temp->colVisited.push_back(mazeQueue.returnFrontColVisited()[i]);
				}

				// Add the current node to the back of the path
				temp->rowVisited.push_back(mazeQueue.returnFrontRow());
				temp->colVisited.push_back(mazeQueue.returnFrontCol());

				// if statement to add a path or the exit to the queue.
				if (mazeArray[mazeQueue.returnFrontRow() + 1][mazeQueue.returnFrontCol()] == 'P' || mazeArray[mazeQueue.returnFrontRow() + 1][mazeQueue.returnFrontCol()] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					mazeQueue.addQueue(temp->state, temp->rowLocation, temp->colLocation, temp->rowVisited, temp->colVisited);
				}

				// delete temp
				delete temp;

			}


			// Check west of the current node to find a path
			if ((mazeQueue.returnFrontCol() - 1 >= 0) && visited[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() - 1] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = mazeQueue.returnFrontRow();
				temp->colLocation = mazeQueue.returnFrontCol() - 1;
				temp->state = mazeArray[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() - 1];

				// Add the new node's path to this node
				for (int i = 0; i < mazeQueue.returnFrontRowVisited().size(); i++)	// add the rows
				{
					temp->rowVisited.push_back(mazeQueue.returnFrontRowVisited()[i]);
				}

				for (int i = 0; i < mazeQueue.returnFrontRowVisited().size(); i++)	// add the columns
				{
					temp->colVisited.push_back(mazeQueue.returnFrontColVisited()[i]);
				}

				// Add the current node to the back of the path
				temp->rowVisited.push_back(mazeQueue.returnFrontRow());
				temp->colVisited.push_back(mazeQueue.returnFrontCol());

				// if statement to add a path or the exit to the queue.
				if (mazeArray[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() - 1] == 'P' || mazeArray[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol() - 1] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					mazeQueue.addQueue(temp->state, temp->rowLocation, temp->colLocation, temp->rowVisited, temp->colVisited);
				}

				// delete temp
				delete temp;

			}



		}

		// Tell the visited array that the current node has been visited
		visited[mazeQueue.returnFrontRow()][mazeQueue.returnFrontCol()] = true;


		// Increment Count
		count++;

		// Pop the first node out of the queue.
		mazeQueue.deleteQueue();

	}

	return;
}


// Function to find the path using a depth first search
void depthFirstSearch(char mazeArray[10][10], int entranceRow, int entranceCol)
{
	// declare variable
	bool exitFound = false;					// variable to hold if the exit has been found or not
	int count = 1;							// Variable to hold how many steps the agent has taken to get to this point
	bool visited[10][10] = { 0 };			// Array to hold which nodes that have already been visited
	int pathThroughMaze[10][10] = { 0 };	// Array to hold the path taken through the maze
	linkedStackType stack;					// queue to process the path
	nodeType * temp;					// temporary pointer to create new nodes to add to the queue
	int numOfNodes = 0;

	// create vectors to be used to add new row and column locations to the directional nodes
	vector<int> northRow;
	vector<int> northCol;
	vector<int> eastRow;
	vector<int> eastCol;
	vector<int> southRow;
	vector<int> southCol; 
	vector<int> westRow;
	vector<int> westCol;

	// start vectors
	vector<int> startRowVisited;
	vector<int> startColVisited;

	// Add the start row and col to the start vectors
	startRowVisited.push_back(entranceRow);
	startColVisited.push_back(entranceCol);


	// Add the entrace node to the queue
	stack.push(mazeArray[entranceRow][entranceCol], entranceRow, entranceCol, startRowVisited, startColVisited);

	// while loop to run until the exit from the maze has been found
	while (!exitFound)
	{
		// Check to make sure that there are still nodes in the stack
		if (stack.isEmptyStack() == true)
		{
			cout << "The exit to the maze was not found." << endl;
			return;
		}
		// create a temp node to hold the current position
		temp = new nodeType;

		// assign values to the temp
		temp->state = stack.top();
		temp->rowLocation = stack.topRow();
		temp->colLocation = stack.topColumn();
		temp->rowVisited = stack.returnTopVisitedRow();
		temp->colVisited = stack.returnTopColsVisited();

		// Evaluate the first node in the queue to see if it is the exit
		if (evaluateNode(temp->state))
		{
			exitFound = true;

			// print the path through the maze after the breadth first search
			cout << "\nThis is the path through the maze discovered by the depth first search:" << endl;
			printPath(pathThroughMaze, mazeArray, stack.returnTopVisitedRow(), stack.returnTopColsVisited(), stack.topRow(), stack.topColumn());

			cout << "\n" << endl;

			// destroy the stack
			stack.~linkedStackType();

			return;

		}
		;
		// Set the step number in the pathArray
		pathThroughMaze[temp->rowLocation][temp->colLocation] = count;

		// pop the stop of the stack
		stack.pop();

		// else statement to move on from the current node.
		if (visited[temp->rowLocation][temp->colLocation] != true && exitFound != true)
		{

			// Check north of the current node to find a path
			if ((temp->rowLocation - 1 >= 0) && visited[temp->rowLocation - 1][temp->colLocation] != true)
			{

				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation - 1][temp->colLocation] == 'P' || mazeArray[temp->rowLocation - 1][temp->colLocation] == 'X')
				{
					// Add the previous node's vectors to the new node
					for (int i = 0; i < temp->rowVisited.size(); i++)		// Add the rows
					{
						northRow.push_back(temp->rowVisited[i]);
					}

					for (int i = 0; i < temp->colVisited.size(); i++)		// add the columns
					{
						northCol.push_back(temp->colVisited[i]);
					}

					// Add the node being travled to's location to the vectors
					northRow.push_back(temp->rowLocation - 1);
					northCol.push_back(temp->colLocation);

					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation - 1][temp->colLocation], temp->rowLocation - 1, temp->colLocation, northRow, northCol);

					// Clear the northRow and northCol for the next iteration
					northRow.clear();
					northCol.clear();
				}
			}

			// Check east of the current node to find a path
			if ((temp->colLocation + 1 < 10) && visited[temp->rowLocation][temp->colLocation + 1] != true)
			{
				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation][temp->colLocation + 1] == 'P' || mazeArray[temp->rowLocation][temp->colLocation + 1] == 'X')
				{
					// add the previsou node's vectors o the new node
					for (int i = 0; i < temp->rowVisited.size(); i++)		// add the rows
					{
						eastRow.push_back(temp->rowVisited[i]);
					}

					for (int i = 0; i < temp->colVisited.size(); i++)		// add the columns
					{
						eastCol.push_back(temp->colVisited[i]);
					}

					// Add the node being traveled to's location to the vectors
					eastRow.push_back(temp->rowLocation);
					eastCol.push_back(temp->colLocation + 1);

					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation][temp->colLocation + 1], temp->rowLocation, temp->colLocation + 1, eastRow, eastCol);

					// CLear the eastRow and eastCol for the next iteration
					eastRow.clear();
					eastCol.clear();
				}
			}


			// Check south of the current node to find a path
			if ((temp->rowLocation + 1 < 10) && visited[temp->rowLocation + 1][temp->colLocation] != true)
			{
				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation + 1][temp->colLocation] == 'P' || mazeArray[temp->rowLocation + 1][temp->colLocation] == 'X')
				{
					// Add the previous node's vectors to the new node
					for (int i = 0; i < temp->rowVisited.size(); i++)		// add the rows
					{
						southRow.push_back(temp->rowVisited[i]);
					}

					for (int i = 0; i < temp->colVisited.size(); i++)		// add the columns
					{
						southCol.push_back(temp->colVisited[i]);
					}

					// add the node being travled to's location to the vectors
					southRow.push_back(temp->rowLocation + 1);
					southCol.push_back(temp->colLocation);
									   					
					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation + 1][temp->colLocation], temp->rowLocation + 1, temp->colLocation, southRow, southCol);

					// Clear the southRow and southCol for the next iteration
					southRow.clear();
					southCol.clear();
				}
			}


			// Check west of the current node to find a path
			if ((temp->colLocation - 1 >= 0) && visited[temp->rowLocation][temp->colLocation - 1] != true)
			{

				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation][temp->colLocation - 1] == 'P' || mazeArray[temp->rowLocation][temp->colLocation - 1] == 'X')
				{
					// add the previous node's vectors to the new node
					for (int i = 0; i < temp->rowVisited.size(); i++)	// add the rows
					{
						westRow.push_back(temp->rowVisited[i]);
					}

					for (int i = 0; i < temp->colVisited.size(); i++)		// add the columns
					{
						westCol.push_back(temp->colVisited[i]);
					}

					//add the node being travled to's location to the vectors
					westRow.push_back(temp->rowLocation);
					westCol.push_back(temp->colLocation - 1);

					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation][temp->colLocation - 1], temp->rowLocation, temp->colLocation - 1, westRow, westCol);

					// Clear the eastRow and eastCol for the next iteration
					westRow.clear();
					westCol.clear();
				}
			}
		}

		// Tell the visited array that the current node has been visited
		visited[temp->rowLocation][temp->colLocation] = true;

		// Increment Count
		count++;

		// delete temp
		delete temp;
	}
	return;
}


// Function to perform the Breadth First Search
void breadthFirstExploration(char mazeArray[10][10], int entranceRow, int entranceCol)
{
	// Declare variable
	bool exitFound = false;					// variable to hold if the exit has been found or not
	int count = 1;							// Variable to hold how many steps the agent has taken to get to this point
	bool visited[10][10] = { 0 };			// Array to hold which nodes that have already been visited
	int pathThroughMaze[10][10] = { 0 };	// Array to hold the path taken through the maze
	linkedQueueType queue;					// queue to process the path
	nodeType * temp;						// temporary pointer to create new nodes to add to the queue
	int numOfNodes = 0;

	// Empty Vectors to facilitate the addQueue function
	vector <int> emptyRow;
	vector<int> emptyCol;

	// Add the entrace node to the queue
	queue.addQueue(mazeArray[entranceRow][entranceCol], entranceRow, entranceCol, emptyRow, emptyCol);

	// while loop to run until the exit from the maze has been found
	while (!exitFound)
	{
		// Set the step number in the pathArray
		pathThroughMaze[queue.returnFrontRow()][queue.returnFrontCol()] = count;

		// Check to make sure there are still nodes in the queue
		if (queue.isEmptyQueue() == true)
		{
			cout << "The exit to the maze was not found" << endl;
			return;
		}

		// Evaluate the first node in the queue to see if it is the exit
		if (evaluateNode(queue.front()))
		{
			exitFound = true;
		}

		// else statement to move on from the current node.
		if (exitFound != true && visited[queue.returnFrontRow()][queue.returnFrontCol()] != true)
		{

			// Check north of the current node to find a path
			if ((queue.returnFrontRow() - 1 >= 0) &&  visited[queue.returnFrontRow() - 1][queue.returnFrontCol()] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = queue.returnFrontRow() - 1;
				temp->colLocation = queue.returnFrontCol();
				temp->state = mazeArray[queue.returnFrontRow() - 1][queue.returnFrontCol()];

				// if statement to add a path or the exit to the queue.
				if (mazeArray[queue.returnFrontRow() - 1][queue.returnFrontCol()] == 'P' || mazeArray[queue.returnFrontRow() - 1][queue.returnFrontCol()] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					queue.addQueue(temp->state, temp->rowLocation, temp->colLocation, emptyRow, emptyCol);
				}

				// delete temp
				delete temp;
			}

			// Check east of the current node to find a path
			if ((queue.returnFrontCol() + 1 < 10) && visited[queue.returnFrontRow()][queue.returnFrontCol() + 1] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = queue.returnFrontRow();
				temp->colLocation = queue.returnFrontCol() + 1;
				temp->state = mazeArray[queue.returnFrontRow()][queue.returnFrontCol() + 1];

				// if statement to add a path or the exit to the queue.
				if (mazeArray[queue.returnFrontRow()][queue.returnFrontCol() + 1] == 'P' || mazeArray[queue.returnFrontRow()][queue.returnFrontCol() + 1] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					queue.addQueue(temp->state, temp->rowLocation, temp->colLocation, emptyRow, emptyCol);
				}

				// delete temp
				delete temp;

			}


			// Check south of the current node to find a path
			if ((queue.returnFrontRow() + 1 < 10) && visited[queue.returnFrontRow() + 1][queue.returnFrontCol()] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = queue.returnFrontRow() + 1;
				temp->colLocation = queue.returnFrontCol();
				temp->state = mazeArray[queue.returnFrontRow() + 1][queue.returnFrontCol()];

				// if statement to add a path or the exit to the queue.
				if (mazeArray[queue.returnFrontRow() + 1][queue.returnFrontCol()] == 'P' || mazeArray[queue.returnFrontRow() + 1][queue.returnFrontCol()] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					queue.addQueue(temp->state, temp->rowLocation, temp->colLocation, emptyRow, emptyCol);
				}

				// delete temp
				delete temp;

			}


			// Check west of the current node to find a path
			if ((queue.returnFrontCol() - 1 >= 0)  && visited[queue.returnFrontRow()][queue.returnFrontCol() - 1] != true)
			{
				// create temporary pointers and nodes
				temp = new nodeType;

				// assign the values to the new node
				temp->rowLocation = queue.returnFrontRow();
				temp->colLocation = queue.returnFrontCol() - 1;
				temp->state = mazeArray[queue.returnFrontRow()][queue.returnFrontCol() - 1];

				// if statement to add a path or the exit to the queue.
				if (mazeArray[queue.returnFrontRow()][queue.returnFrontCol() - 1] == 'P' || mazeArray[queue.returnFrontRow()][queue.returnFrontCol() - 1] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					queue.addQueue(temp->state, temp->rowLocation, temp->colLocation, emptyRow, emptyCol);
				}

				// delete temp
				delete temp;

			}

		}

		// Tell the visited array that the current node has been visited
		visited[queue.returnFrontRow()][queue.returnFrontCol()] = true;


		// Increment Count
		count++;

		// Pop the first node out of the queue.
		queue.deleteQueue();

	}

	// print the path through the maze after the depth first search
	cout << "\nThis is the order that the nodes were explored during the breadth first search:" << endl;
	printEntirePath(pathThroughMaze, mazeArray, emptyRow, emptyCol);

	cout << "\n" << endl;

	// destroy the queue
	queue.~linkedQueueType();

	return;
}


// Function to perform the Breadth First Search
void depthFirstExploration(char mazeArray[10][10], int entranceRow, int entranceCol)
{
	// Declare variable
	bool exitFound = false;					// variable to hold if the exit has been found or not
	int count = 1;							// Variable to hold how many steps the agent has taken to get to this point
	bool visited[10][10] = { 0 };			// Array to hold which nodes that have already been visited
	int pathThroughMaze[10][10] = { 0 };	// Array to hold the path taken through the maze
	linkedStackType stack;					// queue to process the path
	nodeType * temp;					// temporary pointer to create new nodes to add to the queue
	int numOfNodes = 0;

	// empty Vector to facilitate print path
	vector<int> emptyRow;
	vector<int> emptyCol;

	// Add the entrace node to the queue
	stack.push(mazeArray[entranceRow][entranceCol], entranceRow, entranceCol, emptyRow, emptyCol);

	// while loop to run until the exit from the maze has been found
	while (!exitFound)
	{
		 // Check to make sure that there are still nodes in the stack
		if (stack.isEmptyStack() == true)
		{
			cout << "The exit to the maze was not found." << endl;
			return;
		}
		// create a temp node to hold the current position
		temp = new nodeType;

		// assign values to the temp
		temp->state = stack.top();
		temp->rowLocation = stack.topRow();
		temp->colLocation = stack.topColumn();

		// Evaluate the first node in the queue to see if it is the exit
		if (evaluateNode(temp->state))
		{
			exitFound = true;
		}
;
		// Set the step number in the pathArray
		pathThroughMaze[temp->rowLocation][temp->colLocation] = count;

		// pop the stop of the stack
		stack.pop();
		
		// else statement to move on from the current node.
		if (visited[temp->rowLocation][temp->colLocation] != true && exitFound != true)
		{

			// Check north of the current node to find a path
			if ((temp->rowLocation - 1 >= 0) && visited[temp->rowLocation - 1][temp->colLocation] != true)
			{

				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation - 1][temp->colLocation] == 'P' || mazeArray[temp->rowLocation - 1][temp->colLocation] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation - 1][temp->colLocation], temp->rowLocation - 1, temp->colLocation, temp->rowVisited, temp->colVisited);
				}
			}

			// Check east of the current node to find a path
			if ((temp->colLocation + 1 < 10) && visited[temp->rowLocation][temp->colLocation + 1] != true)
			{
				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation][temp->colLocation + 1] == 'P' || mazeArray[temp->rowLocation][temp->colLocation + 1] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation][temp->colLocation + 1], temp->rowLocation, temp->colLocation + 1, temp->rowVisited, temp->colVisited);
				}
			}


			// Check south of the current node to find a path
			if ((temp->rowLocation + 1 < 10) && visited[temp->rowLocation + 1][temp->colLocation] != true)
			{
				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation + 1][temp->colLocation] == 'P' || mazeArray[temp->rowLocation + 1][temp->colLocation] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation + 1][temp->colLocation], temp->rowLocation + 1, temp->colLocation, temp->rowVisited, temp->colVisited);
				}
			}


			// Check west of the current node to find a path
			if ((temp->colLocation - 1 >= 0) && visited[temp->rowLocation][temp->colLocation - 1] != true)
			{

				// if statement to add a path or the exit to the queue.
				if (mazeArray[temp->rowLocation][temp->colLocation - 1] == 'P' || mazeArray[temp->rowLocation][temp->colLocation - 1] == 'X')
				{
					// Add the new node to the queue by derefencing the temp pointer.
					stack.push(mazeArray[temp->rowLocation][temp->colLocation - 1], temp->rowLocation, temp->colLocation - 1, temp->rowVisited, temp->colVisited);
				}
			}
		}

		// Tell the visited array that the current node has been visited
		visited[temp->rowLocation][temp->colLocation] = true;

		// Increment Count
		count++;

		// delete temp
		delete temp;
	}

	// print the path through the maze after the depth first search
	cout << "\nThis is the order nodes were explored using the depth first search:" << endl;
	printEntirePath(pathThroughMaze, mazeArray, emptyRow, emptyCol);

	cout << "\n" << endl;
	
	// destroy the stack
	stack.~linkedStackType();

	return;
}


// FUnction to determine if a node is the exit or not
bool evaluateNode(char currentNode)
{
	// return true if the current node is the exit
	if (currentNode == 'X')
	{
		return true;
	}

	// return false if it is not.
	else
	{
		return false;
	}
}

// function to print the path from the entrance to the exit.
void printPath(int maze[10][10], char mazeArray[10][10], vector<int> rowsVisited, vector<int> colsVisited, int exitRow, int exitCol)
{
	int count = 0;		// count to represent which step is taking place at a node

	// create an array to print
	int printArray[10][10] = { 0 };

	// fill the array with the values from the vectors
	for (int i = 0; i < rowsVisited.size(); i++)
	{
		printArray[rowsVisited[count]][colsVisited[count]] = count;
		count++;
	}

	printArray[exitRow][exitCol] = count;

	cout << "\n" << endl;
	
	// print the maze or the path
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (printArray[i][j] > 0)
			{
				cout << printArray[i][j] << "\t";
			}

			else
			{
				cout << mazeArray[i][j] << "\t";
			}
		}

		cout << "\n";
	}

	cout << "_________________________________________________________________________" << endl;

	return;
}


// Function to evaluate if vectors contain a node
bool visited(int i, int j, std::vector<int>rowsVisited, std::vector<int> colsVisited)
{
	// for loop to cycle through the vectors
	for (int count = 0; count < rowsVisited.size(); count++)
	{
		// return true if i and j are in the vector
		if (rowsVisited[count] == i && colsVisited[count] == j)
		{
			return true;
		}
	}

	return false;
}
