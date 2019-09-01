// BasicMultiThreadingDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*

==========================================================================
Problem statement :

Create a array of 10 integers
Create 2 threads, One thread sorts the array in ascending order, other in descending.

On the main thread, on user input 'D'/'d' display the current status of the array. 
The array must be either ascending or descending. All other states are considered inconsistent state.

When user presses 'Q', quit the program.

==========================================================================
Output :

Original state of numbers array : 10 2 8 6 5 1 9 3 4 7
Enter 'D'/'d' to display current state of the numbers array
Enter 'Q'/'q' to exit
Your input : D
10 9 8 7 6 5 4 3 2 1
Your input : d
10 9 8 7 6 5 4 3 2 1
Your input : d
1 2 3 4 5 6 7 8 9 10
Your input : d
10 9 8 7 6 5 4 3 2 1
Your input : Q
==========================================================================

*/

#include <iostream>
#include <Windows.h>

#include "SortingNumbers.h"
#include "BasicMultiThreadingDemo.h"

using namespace std;

void InteractWithUser(SortingNumbers* numbersForSorting)
{
	char userChoice = 0;

	cout << "Enter 'D'/'d' to display current state of the numbers array" << endl << "Enter 'Q'/'q' to exit" << endl;
	while (numbersForSorting->UserQuitRequestReceived == false)
	{
		cout << "Your input : ";
		cin >> userChoice;

		switch (userChoice)
		{
		case 'Q':
		case 'q':
			numbersForSorting->UserQuitRequestReceived = true;
			break;
		case 'D':
		case 'd':
			numbersForSorting->DisplayNumbers();
			break;
		}
	}

}

int main()
{
	DWORD   threadIds[2];
	HANDLE  threadHandles[2];

	// Creating the data object on the heap instead of stack as it will be shared across threads.
	// If created on stack, each thread has a separate stack, making sharing of data tricky ! Hence, heap.
	SortingNumbers* numbersForSorting = new SortingNumbers();

	cout << "Original state of numbers array : ";
	numbersForSorting->DisplayNumbers();

	threadHandles[0] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		SortingNumbers::AscendingSortingThread,       // thread function name
		numbersForSorting,          // argument to thread function 
		0,                      // use default creation flags 
		&threadIds[0]);   // returns the thread identifier 

	threadHandles[1] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		SortingNumbers::DescendingSortingThread,       // thread function name
		numbersForSorting,          // argument to thread function 
		0,                      // use default creation flags 
		&threadIds[0]);   // returns the thread identifier 

	//Displaying menu and handling commands
	InteractWithUser(numbersForSorting);

	// Waiting for both the threads to safely exit
	WaitForMultipleObjects(2, threadHandles, true, INFINITE);

	// Memory cleanup from the heap
	delete numbersForSorting;

	return 0;
}

