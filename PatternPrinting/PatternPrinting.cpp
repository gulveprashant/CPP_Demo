/* PatternPrinting.cpp : 

Program to print a pattern like below :

1               1
1 2           2 1
1 2 3       3 2 1
1 2 3 4   4 3 2 1
1 2 3 4 5 4 3 2 1
1 2 3 4   4 3 2 1
1 2 3       3 2 1
1 2           2 1
1               1

*/

#include <iostream>

void PrintPattern(int maxNumber)
{
	int rowCount = maxNumber * 2 - 1;
	int columnCount = maxNumber * 2 - 1;
	int rowValueOffset = 0;

	int** matrix = new int*[rowCount] { 0 };
	
	for (int row = 0; row < rowCount; row++)
	{
		matrix[row] = new int[columnCount] {0};
	}

	for (int row = 0; row < rowCount; row++)
	{
		rowValueOffset = maxNumber - abs(maxNumber - row - 1);

		for (int column = 0; column < columnCount; column++)
		{
			int value = abs(maxNumber - column - 1) + rowValueOffset - maxNumber + 1;

			value = (value > 0) ? (rowValueOffset - value + 1) : 0;

			matrix[row][column] = value;
		}
	}


	for (int row = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++)
		{
			int value = matrix[row][column];

			(value != 0) ? std::cout << value << " " : std::cout << "  ";
		}

		std::cout << std::endl;
	}

}

int main()
{
	PrintPattern(5);

	return 0;
}

