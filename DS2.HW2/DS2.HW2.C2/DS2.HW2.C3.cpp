// DS2.HW2.C3.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>

int partition(int*arr, int start, int end);
void quicksort(int*arr, int start, int end);
void swap(int* num1, int* num2);
void test_quicksort();

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


int partition(int *arr, int start, int end)
{
	int pivotValue = arr[end];
	int endOfLowBlock = start - 1;
	int posOfBeChecked = start;
	for (; posOfBeChecked < end; ++posOfBeChecked)
	{
		if (arr[posOfBeChecked] <= pivotValue)
		{
			++endOfLowBlock;
			swap(arr + posOfBeChecked, arr + endOfLowBlock);
		}
	}
	++endOfLowBlock;
	swap(arr + end, arr + endOfLowBlock);

	return endOfLowBlock;
}
void quicksort(int*arr, int start, int end)
{
	int pivot = partition(arr, start, end);
	quicksort(arr, start, pivot - 1);
	quicksort(arr, pivot + 1, end);
}

void swap(int* num1, int* num2)
{
	int tempNum = *num1;
	*num1 = *num2;
	*num2 = tempNum;
}

void test_quicksort()
{
	for (int i = 1; i <= 16; ++i)
	{
		int* testArr = (int*)malloc(sizeof(int)*i);

		free(testArr);
	}

}