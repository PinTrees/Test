#include <iostream>
#include <stdio.h>
#include <string>

// 이진교

using namespace std;

// 2023-03-23 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
struct  Person
{
	const char* name;
	int score;
};

void bubbleSort(char** data, int size) {
	int i, j;
	char* tmp = NULL;

	for (i = size - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (strcmp(data[j], data[j + 1]) > 0) {
				tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
}
void selectionSort(char** data, int size) {
	int i, j, max;
	char* temp;

	for (i = size - 1; i > 0; i--) {
		max = i;
		for (j = 0; j < i; j++) {
			if (strcmp(data[j], data[max]) > 0) {
				max = j;
			}
		}

		temp = data[max];
		data[max] = data[i];
		data[i] = temp;
	}
}
void shellSort(char** data, int size) {
	int i, j, gap;
	char* ist;
	for (gap = size / 2; gap > 0; gap /= 2) {
		for (i = gap; i < size; i++) {
			ist = data[i];
			j = i - gap;
			while (j >= 0 && strcmp(ist, data[j]) < 0)
			{
				data[j + gap] = data[j];
				j -= gap;
			}
			data[j + gap] = ist;
		}
	}
}
void insertSort(char** data, int size) {
	int i, j;
	char* ist;

	for (i = 1; i < size; i++) {
		ist = data[i];
		j = i - 1;
		while (j >= 0 && (strcmp(ist, data[j]) < 0))
		{
			data[j + 1] = data[j];
			j--;
		}

		data[j + 1] = ist;
	}
}
void printArray(char** data, const int size) {
	for (int i = 0; i < size; i++) {
		printf_s("%s, ", data[i]);
	}
	cout << endl;
	cout << endl;
}

void selectionSort(Person data[], int size) {
	int i, j, max;
	Person temp;

	for (i = size - 1; i > 0; i--) {
		max = i;
		for (j = 0; j < i; j++) {
			if (strcmp(data[j].name, data[max].name) > 0) {
				max = j;
			}
		}

		temp = data[max];
		data[max] = data[i];
		data[i] = temp;
	}
}
void printArray(Person data[], int size) {
	printf_s("[ ");
	for (int i = 0; i < size - 1; i++) {
		printf_s("{ 이름: %s, 점수: %d }, ", data[i].name, data[i].score);
	}

	printf_s("{ 이름: %s, 점수: %d } ", data[size - 1].name, data[size - 1].score);
	printf_s(" ]\n\n");
}

void shellSort(int data[], int size) {
	int i, j, gap, ist;

	// 갭을 배열의 절반으로 설정후 반복
	for (gap = size / 2; gap > 0; gap /= 2) {
		// 갭의 크기만큼 떨어진 요소들을 삽입정렬을 이용해 정렬
		for (i = gap; i < size; i++) {
			// 현재 요소값 저장
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
	Person personArr[] = {
		{ "APPP", 10 }, { "DPPP", 20 }, { "GPPP", 30 }, { "DPPP", 40 }, { "EPPP", 50 }, { "FPPP", 60 },
		{ "CPPP", 70 }, { "BPPP", 80 },
	};

	int charArrSize = sizeof(charArr) / sizeof(char*);
	int personArrSize = sizeof(personArr) / sizeof(Person);
	int intArrSize = sizeof(intArr) / sizeof(int);

	//printArray((char**)data, size);
	//bubbleSort((char**)data, size);
	//printArray((char**)data, size);

	//printArray((char**)data, size);
	//selectionSort((char**)data, size);
	//printArray((char**)data, size);

	//printArray((char**)data, size);
	//insertSort((char**)data, size);
	//printArray((char**)data, size);

	printArray((char**)charArr, charArrSize);
	shellSort((char**)charArr, charArrSize);
	printArray((char**)charArr, charArrSize);

	printArray(personArr, personArrSize);
	selectionSort(personArr, personArrSize);
	printArray(personArr, personArrSize);

	printArray(intArr, intArrSize);
	shellSort((int*)intArr, intArrSize);
	printArray(intArr, intArrSize);
}
