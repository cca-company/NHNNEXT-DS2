// DS2.HW1.C1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void insertionSort(int* arr, int length);
int isSorted(int* arr, int num);
void printArr(int* arr, int length);

int _tmain(int argc, _TCHAR* argv[])
{
	int arr1[] = {NULL};	// case1 : 원소가 0개인 경우
	int arr2[] = { 1 };		// case2 : 원소가 1개인 경우
	int arr3[] = { 1,0,9,8,5,6,3,2,4,7};	// case3 : 원소가 2개 이상인 경우

	int arr4[] = { 5, 4, 3, 2, 1 };		// case4 : 원소가 역순으로 정렬된 경우
	int arr5[] = { 1, 2, 3, 4, 5 };		// case5 : 원소가 정렬된 경우
	int arr6[] = { 1, 2, 2, 3, 3, 3 };	// case6 : 중복된 원소가 존재할 경우

	// case1
	printf("case1 : ");
	printArr(arr1, _countof(arr1));
	insertionSort(arr1, _countof(arr1));
	printf("결과 : %d\n", isSorted(arr1, _countof(arr1)));

	// case2
	printf("case2 : ");
	printArr(arr2, _countof(arr2));
	insertionSort(arr2, _countof(arr2));
	printf("결과 : %d\n", isSorted(arr2, _countof(arr2)));

	// case3
	printf("case3 : ");
	printArr(arr3, _countof(arr3));
	insertionSort(arr3, _countof(arr3));
	printf("결과 : %d\n", isSorted(arr3, _countof(arr3)));

	// case4
	printf("case4 : ");
	printArr(arr4, _countof(arr4));
	insertionSort(arr4, _countof(arr4));
	printf("결과 : %d\n", isSorted(arr4, _countof(arr4)));

	// case5
	printf("case5 : ");
	printArr(arr5, _countof(arr5));
	insertionSort(arr5, _countof(arr5));
	printf("결과 : %d\n", isSorted(arr5, _countof(arr5)));

	// case6
	printf("case6 : ");
	printArr(arr6, _countof(arr6));
	insertionSort(arr6, _countof(arr6));
	printf("결과 : %d\n", isSorted(arr6, _countof(arr6)));

	getchar();
	return 0;
}

// 배열을 insertion sort
void insertionSort(int* arr, int length){
	int idx,subIdx,key;

	for (idx = 1; idx < length; ++idx)
	{
		key = arr[idx];
		subIdx = idx - 1;
		while (subIdx >= 0 && arr[subIdx] > key){
			arr[subIdx + 1] = arr[subIdx];
			--subIdx;
		}
		arr[subIdx + 1] = key;
	}

	return;
}

// 배열이 정렬되었는지 확인
int isSorted(int* arr, int num){
	for (int idx = 0; idx < num-1; ++idx)
	{
		if (arr[idx] > arr[idx + 1]) return 0;
	}
	return 1;
}

// 배열의 내용 출력
void printArr(int* arr, int length){
	printf("{");
	for (int idx = 0; idx < length; ++idx)
	{
		printf("%d",arr[idx]);
		if (idx < length - 1) printf(", ");
	}
	printf("} 배열 크기 %d\n",length);
}
