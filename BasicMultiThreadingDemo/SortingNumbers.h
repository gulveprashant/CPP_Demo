#pragma once
#include <Windows.h>

class SortingNumbers
{
private:
	int* _Numbers;
	const int NUMBER_COUNT = 10;
	CRITICAL_SECTION _NumbersLock;

public:
	bool UserQuitRequestReceived;

	SortingNumbers();
	
	~SortingNumbers();
	
	static DWORD WINAPI AscendingSortingThread(LPVOID lpParam);

	static DWORD WINAPI DescendingSortingThread(LPVOID lpParam);

	void DisplayNumbers();
};

