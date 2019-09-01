// DigitsToWords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

A program to convert positive numbers to words

eg: 
1 -> one
12 -> twelve
10000101 -> ten million one hundred one

*/

#include <iostream>
#include <map>
#include <list>

using namespace std;

class DigitToWordsConvertor {
	map<unsigned int, string> numbersDict;
	list<unsigned int> numbersToCheck;

	string convertNumberByPart(int number, list<unsigned int>::iterator numberToCheckIter)
	{
		if (numbersDict.count(number) > 0)
		{
			// Found a match
			string result = numbersDict[number];
			if (number >= 100)
			{
				result = numbersDict[1] + " " + result;
			}

			return result;
		}
		else if (number < 100)
		{
			int unitsPlace = number % 10;
			int tensPlace = number / 10;

			string part1 = numbersDict[tensPlace * 10];
			string part2 = numbersDict[unitsPlace];
			string result = part1 + " " + part2;

			return result;
		}
		else
		{
			unsigned int numberToCheck = 0;

			for (; numberToCheckIter != numbersToCheck.end(); ++numberToCheckIter)
			{
				numberToCheck = *numberToCheckIter;
				if (number > numberToCheck)
				{
					break;
				}
			}

			string part1 = "";
			string part2 = "";
			string part3 = "";
			string result = "";

			unsigned int greaterThanChecked = number / numberToCheck;
			unsigned int lessThanChecked = number % numberToCheck;

			if (numberToCheckIter != numbersToCheck.end())
			{
				part3 = convertNumberByPart(lessThanChecked, ++numberToCheckIter);
			}

			if (greaterThanChecked != 0)
			{
				part1 = convertNumberByPart(greaterThanChecked, numbersToCheck.begin());

				if (numbersDict.count(numberToCheck) > 0)
				{
					part2 = numbersDict[numberToCheck];
				}

				if (lessThanChecked != 0)
				{
					result = part1 + " " + part2 + " " + part3;
				}
				else
				{
					result = part1 + " " + part2;
				}
			}
			else
			{
				result = part3;
			}

			return result;
		}
	}

public:
	DigitToWordsConvertor()
	{
		numbersDict[0] = "Zero";
		numbersDict[1] = "One";
		numbersDict[2] = "Two";
		numbersDict[3] = "Three";
		numbersDict[4] = "Four";
		numbersDict[5] = "Five";
		numbersDict[6] = "Six";
		numbersDict[7] = "Seven";
		numbersDict[8] = "Eight";
		numbersDict[9] = "Nine";
		numbersDict[10] = "Ten";
		numbersDict[11] = "Eleven";
		numbersDict[12] = "Twelve";
		numbersDict[13] = "Thirteen";
		numbersDict[14] = "Fourteen";
		numbersDict[15] = "Fifteen";
		numbersDict[16] = "Sixteen";
		numbersDict[17] = "Seventeen";
		numbersDict[18] = "Eighteen";
		numbersDict[19] = "Nineteen";
		numbersDict[20] = "Twenty";
		numbersDict[30] = "Thirty";
		numbersDict[40] = "Forty";
		numbersDict[50] = "Fifty";
		numbersDict[60] = "Sixty";
		numbersDict[70] = "Seventy";
		numbersDict[80] = "Eighty";
		numbersDict[90] = "Ninety";
		numbersDict[100] = "Hundred";
		numbersDict[1000] = "Thousand";
		numbersDict[1000000] = "Million";
		numbersDict[1000000000] = "Billion";

		numbersToCheck.push_back(1000000000);
		numbersToCheck.push_back(1000000);
		numbersToCheck.push_back(1000);
		numbersToCheck.push_back(100);
	}

	string numberToWords(int num) {
		string numString = "";

		int number = num;

		numString = convertNumberByPart(number, numbersToCheck.begin());

		return numString;
	}
};

int main()
{
	DigitToWordsConvertor convertor;
	int numberToConvert = 10000101;

	string numberInWords = convertor.numberToWords(numberToConvert);
    std::cout << numberToConvert << " --> " << numberInWords;

	return 0;
}
