#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MoveSharp");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

//*
#define ACC 5
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x=100,y=100;
	static int delta=1;
	BOOL bPress;
	RECT rt;
	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd,1,50,NULL);
		return 0;
    // 윈도우 포커스 온 메시지
	case WM_ACTIVATEAPP:
		// 활성화
		if (wParam) {
			SetTimer(hWnd,1,50,NULL);
		} else {
			KillTimer(hWnd,1);
		}
		return 0;
	case WM_TIMER:
		bPress=FALSE;
		// GetKeyState - 
		if (GetKeyState(VK_LEFT) & 0x8000) {
			x-=(delta/ACC);
			bPress=TRUE;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			x+=(delta/ACC);
			bPress=TRUE;
		}
		if (GetKeyState(VK_UP) & 0x8000) {
			y-=(delta/ACC);
			bPress=TRUE;
		}
		if (GetKeyState(VK_DOWN) & 0x8000) {
			y+=(delta/ACC);
			bPress=TRUE;
		}
		if (bPress) {
			delta=min(delta+1,ACC*10);
			SetRect(&rt,x-20,y-40,x+20,y+40);
			InvalidateRect(hWnd,&rt,TRUE);
		} else {
			delta=1;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,x,y,TEXT("#"),1);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/

/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x=100,y=100;
	static int dx=0,dy=0;

	switch (iMessage) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			dx=-8;
			break;
		case VK_RIGHT:
			dx=8;
			break;
		case VK_UP:
			dy=-8;
			break;
		case VK_DOWN:
			dy=8;
			break;
		default:
			return 0;
		}
		x+=dx;
		y+=dy;
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;
	case WM_KEYUP:
		switch (wParam) {
		case VK_LEFT:
		case VK_RIGHT:
			dx=0;
			break;
		case VK_UP:
		case VK_DOWN:
			dy=0;
			break;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,x,y,TEXT("#"),1);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/