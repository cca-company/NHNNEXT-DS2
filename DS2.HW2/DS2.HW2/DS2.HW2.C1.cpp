// DS2.HW2.C1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 주석이 1도 없어서 미안하다 미래의 나와 기여운 혀눅아..........................

#include "stdafx.h"

#define BUFFER_SIZE 100

struct Heap
{
	Heap()
	{
		size = 0;
		element = nullptr;
	}
	Heap(int _size, int* _element)
	{
		size = _size;
		element = _element;
	}
	int size;
	int* element;
};

// max heapify
void max_heapify(Heap* heap, int pos);
void swap(int* num1, int* num2);

// build max heap
Heap* build_max_heap(int* arr, int size);

// heap sort
void heap_sort(int* arr, int size);
int extractMax(Heap* heap, int *maxValue);

// max heap insert
void max_heap_insert(Heap* heap, int key);
void heap_increas_key(Heap* heap, int pos, int key);

// max heap test
void test_heapify(int n);
void test_heapify(int* arr, int size);

int isMaxHeap(Heap* heap, int root);
void printHeap(Heap* heap);
void printArr(int* arr, int size);
Heap* makeSampleHeap(int n);

int _tmain(int argc, _TCHAR* argv[])
{
	test_heapify(0);
	test_heapify(1);
	test_heapify(2);
	test_heapify(10);

	int testArr[BUFFER_SIZE] = {0,4,5,2,1,3,6,7,8,9,10};
	test_heapify(testArr,10);
	heap_sort(testArr, 10);
	printArr(testArr, 10);

	Heap* testHeap = new Heap(10, testArr);
	max_heap_insert(testHeap, 11);
	printHeap(testHeap);

	getchar();
	return 0;
}

void max_heapify(Heap* heap, int pos)
{
	int leftNode = pos * 2;
	int rightNode = pos * 2 + 1;
	int largest = pos;

	if (heap == nullptr) return;

	if (heap->size >= leftNode && 
		heap->element[leftNode] > heap->element[largest])
	{
		largest = leftNode;
	}
	if (heap->size >= rightNode &&
		heap->element[rightNode] > heap->element[largest])
	{
		largest = rightNode;
	}

	if (largest != pos)
	{
		swap(heap->element + largest, heap->element + pos);
		max_heapify(heap, largest);
	}

}

void swap(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

int isMaxHeap(Heap* heap, int root)
{
	if (heap == nullptr) return 0;
	if (root > heap->size) return 1;

	int leftNode = root * 2;
	int rightNode = root * 2 + 1;

	if (leftNode <= heap->size &&
		heap->element[leftNode] > heap->element[root])
	{
		return 0;
	}
	if (rightNode <= heap->size &&
		heap->element[rightNode] > heap->element[root])
	{
		return 0;
	}

	return ( isMaxHeap(heap, leftNode) && isMaxHeap(heap, rightNode) );

}

void printHeap(Heap* heap)
{
	if (heap == nullptr) return;

	printf("{");
	for (int i = 1; i <= heap->size; ++i)
	{
		printf("%d", heap->element[i]);
		if (i < heap->size)	printf(", ");
	}
	printf("}\n");
}

void printArr(int* arr, int size)
{
	if (arr == nullptr) return;

	printf("{");
	for (int i = 1; i <= size; ++i)
	{
		printf("%d", arr[i]);
		if (i < size)	printf(", ");
	}
	printf("}\n");
}

Heap* makeSampleHeap(int n)
{
	int* arr = (int*)malloc(sizeof(int)*n);
	Heap* heap = new Heap(n, arr);
	arr[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		arr[i] = n - i + 1;
	}
	arr[1] = 0;

	return heap;
}

void test_heapify(int n)
{
	Heap* heap = makeSampleHeap(n);

	max_heapify(heap, 1);
	printHeap(heap);
	printf("is max heap : %d \n", isMaxHeap(heap, 1));

}

void test_heapify(int* arr, int size)
{
	Heap* heap = build_max_heap(arr, size);

	max_heapify(heap, 1);
	printHeap(heap);
	printf("is max heap : %d \n", isMaxHeap(heap, 1));
}

Heap* build_max_heap(int* arr, int size)
{
	Heap* heap = new Heap();

	if (arr == nullptr) return heap;
	heap->size = size;
	heap->element = arr;
	
	for (int i = size / 2; i >= 1; --i)
	{
		max_heapify(heap, i);
	}
	return heap;
}

int extractMax(Heap* heap, int *maxValue)
{
	*maxValue = heap->element[1];
	swap(heap->element + 1, heap->element + heap->size);

	heap->size -= 1;
	max_heapify(heap, 1);

	return *maxValue;
}

void heap_sort(int* arr, int size)
{
	Heap* heap = build_max_heap(arr,size);
	for (int i = size; i >= 2; --i)
	{
		swap(heap->element + 1, heap->element + i);
		heap->size -= 1;
		max_heapify(heap, 1);
	}
}

void max_heap_insert(Heap* heap, int key)
{
	heap->size += 1;
	heap->element[heap->size] = INT_MIN;
	heap_increas_key(heap, heap->size, key);
}

void heap_increas_key(Heap* heap, int pos, int key)
{
	if (heap == nullptr) return;
	if (key < heap->element[pos]) return;
	heap->element[pos] = key;

	int parent = pos / 2;
	while (pos > 1 && heap->element[parent] < heap->element[pos])
	{
		swap(heap->element + parent, heap->element + pos);
		pos = parent;
		parent = pos / 2;
	}
}