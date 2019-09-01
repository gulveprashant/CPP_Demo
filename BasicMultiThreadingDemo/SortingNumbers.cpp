#include "SortingNumbers.h"

#include <iostream>

using namespace std;

SortingNumbers::SortingNumbers()
{
	UserQuitRequestReceived = false;
	_Numbers = new int[NUMBER_COUNT] { 10, 2, 8, 6, 5, 1, 9, 3, 4, 7 };

	InitializeCriticalSection(&_NumbersLock);
}

SortingNumbers::~SortingNumbers()
{
	delete[] _Numbers;

	DeleteCriticalSection(&_NumbersLock);
}

DWORD WINAPI SortingNumbers::AscendingSortingThread(LPVOID lpParam)
{
	SortingNumbers* numbersForSorting = reinterpret_cast<SortingNumbers*>(lpParam);

	if (numbersForSorting != NULL)
	{
		while (numbersForSorting->UserQuitRequestReceived == false)
		{
			EnterCriticalSection(&numbersForSorting->_NumbersLock);

			for (int i = 0; i < numbersForSorting->NUMBER_COUNT; i++)
			{
				for (int j = i; j < numbersForSorting->NUMBER_COUNT; j++)
				{
					if (numbersForSorting->_Numbers[i] > numbersForSorting->_Numbers[j])
					{
						int temp = numbersForSorting->_Numbers[i];
						numbersForSorting->_Numbers[i] = numbersForSorting->_Numbers[j];
						numbersForSorting->_Numbers[j] = temp;
					}
				}
			}

			LeaveCriticalSection(&numbersForSorting->_NumbersLock);
		}
	}

	return 0;
}

DWORD WINAPI SortingNumbers::DescendingSortingThread(LPVOID lpParam)
{
	SortingNumbers* numbersForSorting = reinterpret_cast<SortingNumbers*>(lpParam);

	if (numbersForSorting != NULL)
	{
		while (numbersForSorting->UserQuitRequestReceived == false)
		{
			EnterCriticalSection(&numbersForSorting->_NumbersLock);

			for (int i = 0; i < numbersForSorting->NUMBER_COUNT; i++)
			{
				for (int j = i; j < numbersForSorting->NUMBER_COUNT; j++)
				{
					if (numbersForSorting->_Numbers[i] < numbersForSorting->_Numbers[j])
					{
						int temp = numbersForSorting->_Numbers[i];
						numbersForSorting->_Numbers[i] = numbersForSorting->_Numbers[j];
						numbersForSorting->_Numbers[j] = temp;
					}
				}
			}

			LeaveCriticalSection(&numbersForSorting->_NumbersLock);
		}
	}

	return 0;
}

void SortingNumbers::DisplayNumbers()
{
	EnterCriticalSection(&_NumbersLock);

	for (int i = 0; i < NUMBER_COUNT; i++)
	{
		cout << _Numbers[i] << " ";
	}

	cout << endl;

	LeaveCriticalSection(&_NumbersLock);
}