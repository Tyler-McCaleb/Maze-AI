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

	// print the path through the maze after the breadth first search
	cout << "\nThis is the path through the maze after the depth first search" << endl;
	printEntirePath(pathThroughMaze, mazeArray, emptyRow, emptyCol);

	cout << "\n" << endl;

	// destroy the stack
	stack.~linkedStackType();

	return;
}
