#define _CRT_SECURE_NO_WARNNING

#include <iostream>
#include <stdio.h>
#include <string>


#define SWAP(a, b)  a ^= b; b ^= a; a ^= b;


using namespace std;


void ToSWAP(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void shellSort(int data[], int size) {
	int i, j, gap, ist;

	for (gap = size / 2; gap > 0; gap /= 2) {
		for (i = gap; i < size; i++) {
			ist = data[i];
			j = i - gap;
			while (j >= 0 && ist < data[j])
			{
				data[j + gap] = data[j];
				j -= gap;
			}
			data[j + gap] = ist;
		}
	}	
}

void quickSort2(int* data, int start, int end) 
{
	if (start >= end) return;

	int pivot, front, last, tmp;

	pivot = start;
	front = start + 1;
	last = end;

	while (front <= last)
	{
		while (data[front] <= data[pivot] && front <= end) front++;
		while (data[last] > data[pivot] && last >= start) last--;

		if (front > last) break;
		else {
			ToSWAP(data[front], data[last]);
		}
	}
	ToSWAP(data[last], data[pivot]);

	quickSort2(data, start, last - 1);
	quickSort2(data, last + 1, end);
}

void printArray(const int data[], int size) {
	printf_s("[ ");
	for (int i = 0; i < size - 1; i++) {
		printf_s("%d, ", data[i]);
	}
	printf_s("%d ]\n\n", data[size - 1]);
}


int main(void)
{
	const int intArr[] = { 39, 15, 8, 15, 46, 156, 515, 121, 21, 51, 4, 56, 24, 1, 84, 84, 4, 3, 54, 35 };
	const char* charArr[] = { "AN", "JP", "CN", "KO", "BA", "RS", "FN", "DW", "ES", "FS" };


	int charArrSize = sizeof(charArr) / sizeof(char*);
	int intArrSize = sizeof(intArr) / sizeof(int);


	printArray(intArr, intArrSize);
	quickSort2((int*)intArr, 0, intArrSize - 1);
	printArray(intArr, intArrSize);
}