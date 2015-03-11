// DS2.HW1.C2.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <stdlib.h>
#define INT_MAX 2147483647

void mergeSort(int* arr, int* buffArr, int begin, int last);
void merge(int* arr, int* buffArr, int begin, int center, int last);
void copyBlock(int* begin, int* center, int* last, int* buffBegin);
int isSorted(int* arr, int num);
void printArr(int* arr, int length);

int _tmain(int argc, _TCHAR* argv[])
{
	int buff[100] = { INT_MAX, };
	int arr1[] = { NULL };	// case1 : ���Ұ� 0���� ���
	int arr2[] = { 1 };		// case2 : ���Ұ� 1���� ���
	int arr3[] = { 1, 0, 9, 8, 5, 6, 3, 2, 4, 7 };	// case3 : ���Ұ� 2�� �̻��� ���

	int arr4[] = { 5, 4, 3, 2, 1 };		// case4 : ���Ұ� �������� ���ĵ� ���
	int arr5[] = { 1, 2, 3, 4, 5 };		// case5 : ���Ұ� ���ĵ� ���
	int arr6[] = { 1, 2, 2, 3, 3, 3 };	// case6 : �ߺ��� ���Ұ� ������ ���

	// case1
	printf("case1 : ");
	printArr(arr1, _countof(arr1));
	mergeSort(arr1, buff, 0, _countof(arr1) - 1);
	printf("��� : %d\n", isSorted(arr1, _countof(arr1)));

	// case2
	printf("case2 : ");
	printArr(arr2, _countof(arr2));
	mergeSort(arr2, buff, 0, _countof(arr2) - 1);
	printf("��� : %d\n", isSorted(arr2, _countof(arr2)));

	// case3
	printf("case3 : ");
	printArr(arr3, _countof(arr3));
	mergeSort(arr3, buff, 0, _countof(arr3) - 1);
	printf("��� : %d\n", isSorted(arr3, _countof(arr3)));

	// case4
	printf("case4 : ");
	printArr(arr4, _countof(arr4));
	mergeSort(arr4, buff, 0, _countof(arr4) - 1);
	printf("��� : %d\n", isSorted(arr4, _countof(arr4)));

	// case5
	printf("case5 : ");
	printArr(arr5, _countof(arr5));
	mergeSort(arr5, buff, 0, _countof(arr5) - 1);
	printf("��� : %d\n", isSorted(arr5, _countof(arr5)));

	// case6
	printf("case6 : ");
	printArr(arr6, _countof(arr6));
	mergeSort(arr6, buff, 0, _countof(arr6) - 1);
	printf("��� : %d\n", isSorted(arr6, _countof(arr6)));

	getchar();
	return 0;
}


void mergeSort(int* arr, int* buffArr, int begin, int last)
{
	if (last <= begin) return;

	int center = (int)(begin + (last - begin) / 2);
	mergeSort(arr, buffArr, begin, center);
	mergeSort(arr, buffArr, center+1, last);
	merge(arr, buffArr, begin, center, last);
}

void merge(int* arr, int* buffArr, int begin, int center, int last)
{
	int idx, lIdx, rIdx;

	copyBlock(arr + begin, arr + center, arr + last, buffArr + begin);

	lIdx = begin;
	rIdx = center + 2;


	for (idx = begin; idx <= last; ++idx)
	{
		if (buffArr[lIdx] <= buffArr[rIdx])
			arr[idx] = buffArr[lIdx++];
		else
			arr[idx] = buffArr[rIdx++];
	}
}

void copyBlock(int* begin, int* center, int* last, int* buffBegin)
{
	while (begin <= center)
	{
		*buffBegin = *begin;
		buffBegin++;
		begin++;
	}
	*buffBegin = INT_MAX;
	buffBegin++;
	center++;

	while (center <= last)
	{
		*buffBegin = *center;
		buffBegin++;
		center++;
	}
	*buffBegin = INT_MAX;
}

// �迭�� ���ĵǾ����� Ȯ��
int isSorted(int* arr, int num){
	for (int idx = 0; idx < num - 1; ++idx)
	{
		if (arr[idx] > arr[idx + 1]) return 0;
	}
	return 1;
}

// �迭�� ���� ���
void printArr(int* arr, int length){
	printf("{");
	for (int idx = 0; idx < length; ++idx)
	{
		printf("%d", arr[idx]);
		if (idx < length - 1) printf(", ");
	}
	printf("} �迭 ũ�� %d\n", length);
}
