// DS2.HW1.C3.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#define MIN_VALUE -1024

struct Subarray{
	Subarray()
	{
		start = 0, end = 0, sum = 0;
	}
	Subarray(int _start, int _end, int _sum){
		start = _start;
		end = _end;
		sum = _sum;
	}
	int start, end, sum;
};

// n lg n algorithm
Subarray FindMaximumSubarray(int* arr, int start, int end);
Subarray FindMaxCrossingSubarray(int* arr, int start, int middle, int end);

// n^2 algorithm
Subarray FindMaximumSubarray2(int* arr, int size);

// check result is equal
void checkResult(Subarray subArr1, Subarray subArr2);

int _tmain(int argc, _TCHAR* argv[])
{
	int arr1[] = { 0 };
	int arr2[] = { 1 };
	int arr3[] = { -1, 2 };
	int arr4[] = { -1, 5, -3, 9 };
	int arr5[] = { 0, -1, 2, 3, -5, -5, 6, 7, 8, -9 };

	checkResult(FindMaximumSubarray(arr1, 0, 0), FindMaximumSubarray2(arr1, 1));
	checkResult(FindMaximumSubarray(arr2, 0, 0), FindMaximumSubarray2(arr2, 1));
	checkResult(FindMaximumSubarray(arr3, 0, 1), FindMaximumSubarray2(arr3, 2));
	checkResult(FindMaximumSubarray(arr4, 0, 3), FindMaximumSubarray2(arr4, 4));
	checkResult(FindMaximumSubarray(arr5, 0, 9), FindMaximumSubarray2(arr5, 10));

	getchar();
	return 0;
}


Subarray FindMaximumSubarray(int* arr, int start, int end)
{
	if (arr == nullptr) return Subarray();
	if (start == end) return Subarray(start, end, arr[start]);

	int mid = start + (end-start) / 2;
	Subarray leftArr, rightArr, midArr;
	leftArr = FindMaximumSubarray(arr, start, mid);
	rightArr = FindMaximumSubarray(arr, mid+1, end);
	midArr = FindMaxCrossingSubarray(arr, start, mid, end);

	if (leftArr.sum >= rightArr.sum && leftArr.sum >= midArr.sum)	return leftArr;
	if (midArr.sum >= leftArr.sum && midArr.sum >= rightArr.sum)	return midArr;
	if (rightArr.sum >= leftArr.sum && rightArr.sum >= midArr.sum)	return rightArr;
}

Subarray FindMaxCrossingSubarray(int* arr, int start, int middle, int end)
{
	int leftSum = MIN_VALUE, rightSum = MIN_VALUE;
	int sum = 0, maxLeft = 0, maxRight = 0;

	if (arr == nullptr) return Subarray(-1,-1,-1);

	// find left max subarray
	for (int i = middle; i >= start; --i)
	{
		sum += arr[i];
		if (sum > leftSum)
		{
			leftSum = sum;
			maxLeft = i;
		}
	}

	sum = 0;
	// find left max subarray
	for (int i = middle+1; i <= end; ++i)
	{
		sum += arr[i];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxRight = i;
		}
	}

	return Subarray(maxLeft, maxRight, leftSum + rightSum);
}

// n^2 algorithm
Subarray FindMaximumSubarray2(int* arr, int size)
{
	int maxStart = 0, maxEnd = 0, sum = 0;
	int maxSum = MIN_VALUE;

	if (arr == nullptr) return Subarray(-1, -1, -1);

	for (int i = 0; i < size; ++i)
	{
		sum = 0;
		for (int j = i; j < size; ++j)
		{
			sum += arr[j];
			if (sum > maxSum)
			{
				maxSum = sum;
				maxStart = i;
				maxEnd = j;
			}
		}
	}

	return Subarray(maxStart, maxEnd, maxSum);
}


void checkResult(Subarray subArr1, Subarray subArr2)
{
	if ((subArr1.start != subArr2.start) ||
		(subArr1.end != subArr2.end) ||
		(subArr1.sum != subArr2.sum))
	{
		printf("<result is not equal!!>\n");
		return;
	}

	printf("<result>\n");
	printf("start : %d\n", subArr1.start);
	printf("end : %d\n", subArr1.end);
	printf("sum : %d\n\n", subArr1.sum);

	return;
}