// DS2.HW2.C7.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>

int selectKth(int *arr, int first, int last, int kth);
int randomized_partition(int*arr, int start, int end);
void swap(int* num1, int* num2);

int _tmain(int argc, _TCHAR* argv[])
{
	int testArr[] = { 1, 29, 23, 4, 5, 63, 97, 8, 9, 0 };
	int kth = 9;
	printf("%d번째 작은 원소는 %d입니다.", kth, selectKth(testArr, 0, 9, kth));
	getchar();
	return 0;
}

int selectKth(int *arr, int first, int last, int kth)
{
	if (arr == nullptr) return -1;
	if (kth < first || kth > last) return -1;
	int pivot = randomized_partition(arr, first, last);
	if (pivot > kth)
	{
		return selectKth(arr, first, pivot - 1, kth);
	}
	else if (pivot < kth)
	{
		return selectKth(arr, pivot+1, last, kth);
	}
	else
	{
		return arr[pivot];
	}
}

int randomized_partition(int *arr, int start, int end)
{
	if (arr == nullptr) return -1;

	srand(time(NULL));
	int randomIndex = start + rand() % (end - start + 1);
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

void swap(int* num1, int* num2)
{
	int tempNum = *num1;
	*num1 = *num2;
	*num2 = tempNum;
}