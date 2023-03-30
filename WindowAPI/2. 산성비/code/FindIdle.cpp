#include <windows.h>
#include "object.h"
#include "list.h"
#include "player.h"
#include "tstring.h"
#define _UNICODE

using namespace std;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="FindIdle";
HWND hWndMain;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); 
	hWndMain = hWnd; 

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

Box** objects;				// 오브젝트
Player* player;				// 플래이어

int score = 0;				// 점수
int gameCount = 100;			// 타이머
int width = 0;				// 창 가로 크기
int height = 0;				// 창 세로 크기
HBITMAP hBit = NULL;


List<TCHAR*>* stringsSet;
List<SSS*>* strings;

// 더블버퍼링 최종 화면 출력 함수
void DrawBitmap(HDC hdc, HBITMAP hBit)
{
	HBITMAP OldBitmap;
	BITMAP bit;

	// 메모리화면에 전달받은 비트맵을 출력
	HDC MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	// 최종적으로 화면에 출력
	GetObject(hBit, sizeof(BITMAP), &bit);
	BitBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);

	// 해제
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

// 더블버퍼링 화면 처리 함수
void OnRefesh()
{
	RECT crt;
	GetClientRect(hWndMain, &crt);
	HDC hdc = GetDC(hWndMain);
	if (hBit == NULL) hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	// UI 출력
	TCHAR str[128];
	TCHAR gameTimerStr[128];
	wsprintf(str, TEXT("현재 점수는 %d점 입니다."), score);
	wsprintf(gameTimerStr, TEXT("남은 시간 %d초"), gameCount);
	TextOut(hMemDC, 10, 40, str, lstrlen(str));
	TextOut(hMemDC, 10, 5, gameTimerStr, lstrlen(gameTimerStr));

	// 문자열 출력
	strings->ForEach([&](SSS* data) {
		data->DrawCall(hMemDC);
	});

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);  

	InvalidateRect(hWndMain, NULL, FALSE);
}

#define ID_EDIT1 100
#define ID_EDIT2 101
HWND hEdit_Input, hEdit2;


WNDPROC OldEditProc;

// 사용자 입력값과 단어 확인 함수
void Check() {
	// 에디트윈도우에서 값 획득
	TCHAR arr[128] = { 0 };
	int len = GetWindowText(hEdit_Input, arr, 128);

	// 입력창 텍스트 초기화
	SetWindowTextA(hEdit_Input, "");

	// 입력값 비교처리
	strings->ForEach([&](SSS* data) {
		if (wcscmp((WCHAR*)arr, (WCHAR*)(data->string->characters)) == 0) {
			score++;
			data->isDisbale = true;
		}
	});
}

// 사용자 입력창 메시지 처리 함수
LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CHAR:
		if (wParam == VK_RETURN) {
			Check();	
			return 0;
		}
		break;
	}
	return CallWindowProc(OldEditProc, hWnd, iMessage, wParam, lParam);
}


// 문자열 생성 함수
void CreateObject()
{
	srand((unsigned int)time(NULL));

	stringsSet = new List<TCHAR*>;
	strings = new List<SSS*>;

	stringsSet->Add("다이어트");
	stringsSet->Add("단무지");
	stringsSet->Add("돼지");
	stringsSet->Add("앨범");
	stringsSet->Add("자유의여신상");
	stringsSet->Add("놀이공원");
	stringsSet->Add("새우");
	stringsSet->Add("냄비");
	stringsSet->Add("미술관");
	stringsSet->Add("닭고기");
	stringsSet->Add("병");
	stringsSet->Add("옥상");
	stringsSet->Add("팩스");
	stringsSet->Add("당근");
	stringsSet->Add("선물");
	stringsSet->Add("롯데리아");
	stringsSet->Add("축제");
	stringsSet->Add("사위");
	stringsSet->Add("거북이");
	stringsSet->Add("철도");
	stringsSet->Add("식당");
	stringsSet->Add("포장마차");
	stringsSet->Add("발가락");
	stringsSet->Add("구멍");
	stringsSet->Add("연주");

	// 문자열 객체 생성
	for (int i = 0; i < 10; i++) {
		strings->Add(new SSS(width - 100, 100, stringsSet->GetRandom()));
	}
}

// 문자열 소환 함수
void ResponeObject()
{
	strings->Add(new SSS(width - 100, 100, stringsSet->GetRandom()));
}


// 문자열 이동 함수
void ObjectMove()
{
	List<SSS*> deleteList;

	strings->ForEach([&](SSS* data) {
		if (data->y > height - 25) {
			score--;
			data->isDisbale = true;
		}
		data->Move();

		if (data->isDisbale) {
			deleteList.Add(data);
		}
	});

	// 람다식을 통한 반복중 리스트 구조가 변경될 경우 오류가 발생할 수 있으므로 구조 변경 코드는 항상 같은 곳에서 처리
	// 비활성화된 객체 제거 - 제거가 아닌 재사용 하는 코드로 변경 필요. 재사용시 화면상 최대 소환 가능 개수를 지정해야함
	deleteList.ForEach([&](SSS* data) {
		strings->remove(data);
	});
}

void Init() {
	srand((unsigned int)time(NULL));

	HDC hdc = GetDC(hWndMain);
	RECT rectT;
	GetClientRect(hWndMain, &rectT);

	if (hBit == NULL) hBit = CreateCompatibleBitmap(hdc, rectT.right, rectT.bottom);
	HDC hMemDC = CreateCompatibleDC(hdc);

	HBITMAP OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &rectT, GetSysColorBrush(COLOR_WINDOW));

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);

	InvalidateRect(hWndMain, NULL, FALSE);

	width = rectT.right - rectT.left;
	height = rectT.bottom - rectT.top;

	player = new Player();
	player->SetPositin(0, 50);
	CreateObject();

	hEdit_Input = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		width / 2 - 200, height - 50, 400, 25, hWndMain, (HMENU)ID_EDIT1, g_hInst, EditSubProc);
	SetFocus(hEdit_Input);
	OldEditProc = (WNDPROC)SetWindowLongPtr(hEdit_Input, GWLP_WNDPROC, (LONG_PTR)EditSubProc);
}



LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	BOOL bPress;
	RECT winSize;

	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd; 
		Init();
		SetTimer(hWnd, 1, 10, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		SetTimer(hWnd, 3, 300, NULL);
		return 0;
		 
	case WM_ACTIVATEAPP:
		if (wParam) {
			SetTimer(hWnd, 1, 30, NULL);
		}
		else { 
			KillTimer(hWnd, 1);
		}
		return 0;

	case WM_TIMER:
		OnRefesh();

		switch (wParam)
		{
		case 1:
			ObjectMove();
			break;
		case 2:
			gameCount--;
			break;
		case 3:
			ResponeObject();
			break;
		default:
			break;
		}
		if (gameCount <= 0) {
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (hBit) DrawBitmap(hdc, hBit);
		EndPaint(hWnd, &ps); 
		return 0;

	case WM_DESTROY:
		if (hBit) DeleteObject(hBit); 
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
