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

Box** objects;				// ������Ʈ
Player* player;				// �÷��̾�

int score = 0;				// ����
int gameCount = 100;			// Ÿ�̸�
int width = 0;				// â ���� ũ��
int height = 0;				// â ���� ũ��
HBITMAP hBit = NULL;


List<TCHAR*>* stringsSet;
List<SSS*>* strings;

// ������۸� ���� ȭ�� ��� �Լ�
void DrawBitmap(HDC hdc, HBITMAP hBit)
{
	HBITMAP OldBitmap;
	BITMAP bit;

	// �޸�ȭ�鿡 ���޹��� ��Ʈ���� ���
	HDC MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	// ���������� ȭ�鿡 ���
	GetObject(hBit, sizeof(BITMAP), &bit);
	BitBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);

	// ����
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

// ������۸� ȭ�� ó�� �Լ�
void OnRefesh()
{
	RECT crt;
	GetClientRect(hWndMain, &crt);
	HDC hdc = GetDC(hWndMain);
	if (hBit == NULL) hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	// UI ���
	TCHAR str[128];
	TCHAR gameTimerStr[128];
	wsprintf(str, TEXT("���� ������ %d�� �Դϴ�."), score);
	wsprintf(gameTimerStr, TEXT("���� �ð� %d��"), gameCount);
	TextOut(hMemDC, 10, 40, str, lstrlen(str));
	TextOut(hMemDC, 10, 5, gameTimerStr, lstrlen(gameTimerStr));

	// ���ڿ� ���
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

// ����� �Է°��� �ܾ� Ȯ�� �Լ�
void Check() {
	// ����Ʈ�����쿡�� �� ȹ��
	TCHAR arr[128] = { 0 };
	int len = GetWindowText(hEdit_Input, arr, 128);

	// �Է�â �ؽ�Ʈ �ʱ�ȭ
	SetWindowTextA(hEdit_Input, "");

	// �Է°� ��ó��
	strings->ForEach([&](SSS* data) {
		if (wcscmp((WCHAR*)arr, (WCHAR*)(data->string->characters)) == 0) {
			score++;
			data->isDisbale = true;
		}
	});
}

// ����� �Է�â �޽��� ó�� �Լ�
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


// ���ڿ� ���� �Լ�
void CreateObject()
{
	srand((unsigned int)time(NULL));

	stringsSet = new List<TCHAR*>;
	strings = new List<SSS*>;

	stringsSet->Add("���̾�Ʈ");
	stringsSet->Add("�ܹ���");
	stringsSet->Add("����");
	stringsSet->Add("�ٹ�");
	stringsSet->Add("�����ǿ��Ż�");
	stringsSet->Add("���̰���");
	stringsSet->Add("����");
	stringsSet->Add("����");
	stringsSet->Add("�̼���");
	stringsSet->Add("�߰��");
	stringsSet->Add("��");
	stringsSet->Add("����");
	stringsSet->Add("�ѽ�");
	stringsSet->Add("���");
	stringsSet->Add("����");
	stringsSet->Add("�Ե�����");
	stringsSet->Add("����");
	stringsSet->Add("����");
	stringsSet->Add("�ź���");
	stringsSet->Add("ö��");
	stringsSet->Add("�Ĵ�");
	stringsSet->Add("���帶��");
	stringsSet->Add("�߰���");
	stringsSet->Add("����");
	stringsSet->Add("����");

	// ���ڿ� ��ü ����
	for (int i = 0; i < 10; i++) {
		strings->Add(new SSS(width - 100, 100, stringsSet->GetRandom()));
	}
}

// ���ڿ� ��ȯ �Լ�
void ResponeObject()
{
	strings->Add(new SSS(width - 100, 100, stringsSet->GetRandom()));
}


// ���ڿ� �̵� �Լ�
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

	// ���ٽ��� ���� �ݺ��� ����Ʈ ������ ����� ��� ������ �߻��� �� �����Ƿ� ���� ���� �ڵ�� �׻� ���� ������ ó��
	// ��Ȱ��ȭ�� ��ü ���� - ���Ű� �ƴ� ���� �ϴ� �ڵ�� ���� �ʿ�. ����� ȭ��� �ִ� ��ȯ ���� ������ �����ؾ���
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
