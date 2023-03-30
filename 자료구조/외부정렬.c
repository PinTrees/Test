#define _CRT_SECURE_NO_WARNINGS
	
#include <stdio.h>
#include <stdlib.h>	
	
//using namespace std;
	
#define BFRSIZE 4
#define RCDSIZE (sizeof(int))

struct fileInfo {
	FILE* fp;
	char fname[100];
	int min;
	int is_eof;
};

void bubbleSort(int *buf, int len);

void ToSWAP(int* a, int* b) {
	int t = a;
	a = b;
	b = t;
}


void bubbleSort(int* buf, int len) {
	int i, j;
	for (i = len - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (buf[j] > buf[j + 1])
				ToSWAP(buf[j], buf[j + 1]);
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
	int i, f;
	FILE* srcFile, * dstFile;

	// 소스 데이터 파일 생성
	int dataArr[] = { 80,50,10,40,20,60,70,30,1,50,504,447,15,154,44,4,5,4,57,4,4,4,54,4,74,74854,64,64,6,6,7,4,4,64,44 };
	int length = sizeof(dataArr) / sizeof(int);

	srcFile = fopen("src.data", "wb");
	fwrite(dataArr, sizeof(int), length, srcFile);
	fclose(srcFile);

	srcFile = fopen("src.data", "rb");
	dstFile = fopen("dst.data", "wb");

	fseek(srcFile, 0L, SEEK_END);
	int rcdNumber	= (int)(ftell(srcFile) / RCDSIZE);			// 전체목록의 데이터 개수 확인
	int fNumber		= rcdNumber / BFRSIZE + 1;					// 전체목록의 분 파일 생성 개수 산출


	//임시파일들의 정보를 저장할 구조체 배열 생성
	struct fileInfo* tmpFiles = (struct fileInfo*)malloc(sizeof(struct fileInfo) * fNumber);
	if (tmpFiles == NULL) return 0;

	// 내부 정렬에 사용할 버퍼 생성
	int* buffer = (int*)malloc(BFRSIZE * RCDSIZE);
	if (buffer == NULL) return 0;

	//임시파일 생성하고 wb 모드로 열기
	for (i = 0; i < fNumber; i++)
	{
		sprintf(tmpFiles[i].fname, "%stmp_%d.data", "t", i);
		tmpFiles[i].fp		 = fopen(tmpFiles[i].fname, "wb");
		tmpFiles[i].min		 = 0;				// 임시파일 안에 저장된 값중에서 최소값을 저장할 변수
		tmpFiles[i].is_eof	 = 0;				// is_eof == 1 이면 파일 끝이 도달한 것, 0이면 아직 도달하지 않은 것
		
	}
	
	// 각각의 분리 파일에 대한 정렬
	fseek(srcFile, 0L, SEEK_SET);
	for (f = 0; f < fNumber - 1; f++)
	{
		fread		(buffer, RCDSIZE, BFRSIZE, srcFile);
		bubbleSort	(buffer, BFRSIZE);							// 정렬
		fwrite		(buffer, RCDSIZE, BFRSIZE, tmpFiles[f].fp);
	}
	
	// 나머지 값은 버퍼 사이즈를 특정할 수 없기 때문에 나머지 값으로 계산
	// 소스파일에서 마지막 남은 데이터(BFRSIZE보다 작거나 같은 수의 남은 데이터)를 버퍼로 읽어와서 정렬하고 마지막 임시파일에 저장
	fread		(buffer, RCDSIZE, rcdNumber % BFRSIZE, srcFile);
	bubbleSort	(buffer, rcdNumber % BFRSIZE);
	fwrite		(buffer, RCDSIZE, rcdNumber % BFRSIZE, tmpFiles[f].fp);
	

	// wb 모드로 열린 임시파일을 모두 닫기
	for (f = 0; f < fNumber; f++)	fclose(tmpFiles[f].fp);

	// 임시파일 병합을 위해 임시파일을 rb 모드로 열기
	for (f = 0; f < fNumber; f++)	tmpFiles[f].fp = fopen(tmpFiles[f].fname, "rb");
	
	// 쓰기 위한 병합파일 포인터 초기화
	rewind(dstFile);
	int minFile = 0;
	int minValue = 0;
	int frByte;

	//각 임시파일에서 최소값을 min에 대입하고, 파일의 끝에 도달했는지 확인
	for (f = 0; f < fNumber; f++)
	{
		rewind(tmpFiles[f].fp);		// 파일 포인터 위치 처음으로 변경

		// 각 분리파일 최솟값 초기화
		frByte = fread(&(tmpFiles[f].min), RCDSIZE, 1, tmpFiles[f].fp);
		// 파일 값이 없다면 파일 종료 - 예외처리
		if (frByte == 0) tmpFiles[f].is_eof = 1;
	}


	int done;
	// 각 분리 파일을 순회하면서 가로로 읽음
	// 각 분리파일들의 가장 작은 파일의 값을 저장 반복
	// 모두 저장된 파일은 종료
	while (1)
	{
		done = 1;	

		// 임시파일 중 하나라도 파일 끝에 도달하지 않은 것이 있으면 종료 안됨
		for (f = 0; f < fNumber; f++) if (!tmpFiles[f].is_eof) done = 0;

		// 모든 파일이 기록되었다면 종료
		if (done) break;
		minFile = 0;

		// 파일 끝에 도달하지 않은 첫번째 임시파일 번호를 minFile에 저장
		// 파일중 마지막에 도달한 파일이 존재할 가능성이 있으므로 반복문으로 처리해야 함
		for (f = 0; f < fNumber; f++)
		{
			// 파일이 끝났다면 미처리
			if	 (tmpFiles[f].is_eof == 1) continue;
			// 현재 순회중 가장 작은 값을 첫번째 파일값으로 초기화
			else	minFile = f; break;
			
		}

		// 아직 끝에 도달하지 않은 임시파일 중에서 min 값이 제일 작은 값을 가진 파일 번호를 minFile에 대입
		// 파일 값을 순회하며 가장 작은 값을 찾음
		for (f = 0; f < fNumber; f++)
		{
			if (tmpFiles[f].is_eof == 1) continue;
			else if (tmpFiles[minFile].min > tmpFiles[f].min) minFile = f;
		}

		
		// minFile의 min 값을 dstFile에 쓰기
		// 최종정렬파일에 현재 순회중 가장 작은 값을 기록
		fwrite(&(tmpFiles[minFile].min), RCDSIZE, 1, dstFile);

		// minFile의 다음 레코드를 읽어서 minFile의 min 값으로 대입
		// 해당 분리파일의 min 값을 다음값으로 변경
		// 파일의 마지막이라면 해당 분리파일 종료 기록
		frByte = fread(&(tmpFiles[minFile].min), RCDSIZE, 1, tmpFiles[minFile].fp);
		if (frByte == 0) tmpFiles[minFile].is_eof = 1;
	} // while

	// 열려있는 레코드 파일 모두 종료
	for (f = 0; f < fNumber; f++)
	{
		fclose(tmpFiles[f].fp);
		_unlink(tmpFiles[f].fname);
	}
	
	// 최종 정렬파일도 종료
	fclose(srcFile);
	fclose(dstFile);
	free(tmpFiles);


	// 정렬된 결과 확인
	int data;
	srcFile = fopen("src.data", "rb");
	printf("srcFile : ");
	for (i = 0; i < rcdNumber; i++)
	{
		fread(&data, RCDSIZE, 1, srcFile);
		printf(" %d ", data);
	}
	printf(" \n\n");
	fclose(srcFile);


	dstFile = fopen("dst.data", "rb");
	printf("dstFile : ");
	for (i = 0; i < rcdNumber; i++)
	{
		fread(&data, RCDSIZE, 1, dstFile);
		printf(" %d ", data);
	}
	printf(" \n\n");
	fclose(dstFile);

	return 0;
}