// DS2.HW2.C5.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>

void count_sort(int* arr, int size, int maxValue);
void count_sort_for_radix(int* arr, int size, int digit);
void radix_sort(int* arr, int size, int digit);
int* copy_arr(int* arr, int size);
void printArr(int* arr, int size);
int extract_digit_value(int num, int digit);

int _tmain(int argc, _TCHAR* argv[])
{
	int testArr[] = { 6, 2, 15, 5, 13, 1, 0, 5, 9, 10 };
	count_sort(testArr, 10, 15);
	printArr(testArr, 10);

	int testArr2[] = { 45, 21, 14, 82, 68, 77, 30, 56, 93, 19 };
	radix_sort(testArr2, 10, 2);
	printArr(testArr2, 10);
	getchar();

	return 0;
}

void count_sort(int* arr, int size, int maxValue)
{
	int* countOfNum = (int*)malloc(sizeof(int)*(maxValue+1));
	int* inputArr = copy_arr(arr, size);
	int valueOfElement, posOfElement;

	for (int i = 0; i <= maxValue; ++i)
	{
		countOfNum[i] = 0;
	}

	for (int i = 0; i < size; ++i)
	{
		valueOfElement = inputArr[i];
		countOfNum[valueOfElement]++;
	}

	for (int i = 1; i <= maxValue; ++i)
	{
		countOfNum[i] = countOfNum[i - 1] + countOfNum[i];
	}

	for (int i = size - 1; i >= 0; --i)
	{
		valueOfElement = inputArr[i];
		posOfElement = --countOfNum[valueOfElement];

		arr[posOfElement] = valueOfElement;
	}

	free(countOfNum);
	free(inputArr);
}

int* copy_arr(int* arr, int size)
{
	int* copyArr = (int*)malloc(sizeof(int)*size);
	for (int i = 0; i < size; ++i)
	{
		copyArr[i] = arr[i];
	}
	return copyArr;
}

void printArr(int* arr, int size)
{
	if (arr == nullptr) return;

	printf("{");
	for (int i = 0; i < size; ++i)
	{
		printf("%d", arr[i]);
		if (i < size-1)	printf(", ");
	}
	printf("}\n");
}

void radix_sort(int* arr, int size, int digit)
{
	for (int i = 1; i <= digit; ++i)
	{
		count_sort_for_radix(arr, size, i);
	}
}

int extract_digit_value(int num, int digit)
{
	int multiplier = 1;
	int extractNum = 0;
	for (int i = 1; i <= digit; ++i)
	{
		multiplier *= 10;
	}
	extractNum = num%multiplier;
	extractNum = (extractNum * 10) / multiplier;
	return extractNum;
}

void count_sort_for_radix(int* arr, int size, int digit)
{
	int countOfNum[10] = { 0, };
	int* inputArr = copy_arr(arr, size);
	int valueOfElement, posOfElement;

	for (int i = 0; i < size; ++i)
	{
		valueOfElement = extract_digit_value(inputArr[i], digit);
		++countOfNum[valueOfElement];
	}

	for (int i = 1; i <= 9; ++i)
	{
		countOfNum[i] = countOfNum[i - 1] + countOfNum[i];
	}

	for (int i = size - 1; i >= 0; --i)
	{
		valueOfElement = extract_digit_value(inputArr[i], digit);
		posOfElement = --countOfNum[valueOfElement];

		arr[posOfElement] = inputArr[i];
	}

	free(inputArr);
}