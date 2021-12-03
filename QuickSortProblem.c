#include<stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 
#define MAX_NUMBERS 4
#define MAX_DIGITS 2

/**

	Sorting arrays of decimal integers in a way that the following concatenation 
	results in the largest number possible comes with a number of problems. 
	Take an array of two numbers: 9, 27. The desired result would be: 279.
	The question arises how to sort the array so that the algorithm deems 
	9 greater than 27 in this specific case. 
	One possible solution is to not compare the numbers themselves,
	but the possible results of concatenation: 927, and 279. 
	The comparison is the following: 
	Is first number * 10 ^ second number's digits + second number larger than
	second number * 10 ^ first number's digits + first number? 
	This comparison can be implemented in a quick sort algorithm.

**/

FILE* CreateTestFile(char* FileName, FILE* TestFile)
{
	if ((TestFile = fopen(FileName, "w+")) == NULL)
	{
		printf(" cannot open file");
		exit(-1);
	}
	return TestFile;
}

int ResultOut(int Result[MAX_NUMBERS][2], FILE* TestFile)
{
	for (int i = 0; i < MAX_NUMBERS; i++)
	{
		fprintf(TestFile, "%d", Result[i][0]);
		fprintf(TestFile, "%c", ' ');
	}
	fprintf(TestFile, "%c", '\n');
	return 1;
}

int DigitCounter(int* Numbers, int NumAndNumOfDigits[MAX_NUMBERS][2])
{
	for (int i = 0; i < MAX_NUMBERS; i++)
	{
		int Number = Numbers[i];
		NumAndNumOfDigits[i][0] = Numbers[i];
		NumAndNumOfDigits[i][1] = 0;
		while (Number > 0)
		{
			Number /= 10;
			NumAndNumOfDigits[i][1]++;
		}
	}
	return 1;
}

inline void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[MAX_NUMBERS][2], int low, int high)
{
	//int Pivot = arr[low][0];
	int i = low;
	int j = high;

	while (i < j)
	{
		for (int n = 0; n < MAX_NUMBERS; n++)
		{
			if (arr[i][0] * pow(10, arr[low][1]) + arr[low][0] >= arr[low][0] * pow(10, arr[i][1]) + arr[i][0])
			{
				i++;
			}

			if (arr[j][0] * pow(10, arr[low][1]) + arr[low][0] < arr[low][0] * pow(10, arr[j][1]) + arr[j][0])
			{
				j--;
			}
		}

		if (i < j)
		{
			swap(&arr[i][0], &arr[j][0]);
			swap(&arr[i][1], &arr[j][1]);
		}
	}

	swap(&arr[low][0], &arr[j][0]);
	swap(&arr[low][1], &arr[j][1]);

	return j;
}

int Quicksort(int arr[MAX_NUMBERS][2], int low, int high)
{
	if (low < high)
	{

		int j = partition(arr, low, high);

		Quicksort(arr, low, j - 1);
		Quicksort(arr, j + 1, high);

	}
	return 1;
}

int Test(int* TestArr, FILE* TestFile)
{
	int NumAndNumOfDigits[MAX_NUMBERS][2];//numbers and digitscount
	DigitCounter(TestArr, NumAndNumOfDigits);
	//ResultOut(NumAndNumOfDigits, TestFile);
	Quicksort(NumAndNumOfDigits, 0, MAX_NUMBERS - 1);
	ResultOut(NumAndNumOfDigits, TestFile);

	return 1;
}

int main()
{
	FILE* TestFile;
	TestFile = CreateTestFile("TEST_RESULT.txt", TestFile);
	//fprintf(TestFile, "%c", '\n');

	int TestZero[MAX_NUMBERS] = { 3, 1, 4, 2 };
	int TestA[MAX_NUMBERS] = { 33, 22, 44, 22 };
	int TestB[MAX_NUMBERS] = { 8, 86, 88, 8 };

	int TestOne[MAX_NUMBERS] = {9, 86, 99, 96};
	int TestTwo[MAX_NUMBERS] = {86, 9, 99, 96};
	//int TestThree[MAX_NUMBERS] = {86, 96, 99, 99};
	int TestThree[MAX_NUMBERS] = {99, 96, 99, 86};//9696
	//int TestThree[MAX_NUMBERS] = {89, 86, 89, 96};
	int TestFour[MAX_NUMBERS] = {86, 99, 9, 96};
	
	Test(TestOne, TestFile);
	Test(TestTwo, TestFile);
	Test(TestThree, TestFile);
	Test(TestFour, TestFile);

	Test(TestZero, TestFile);
	Test(TestA, TestFile);
	Test(TestB, TestFile);

	return 1;
}