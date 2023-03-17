#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="FindIdle";
HWND hWndMain;

void OnIdle();

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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
	hWndMain=hWnd;

	
/* �������� ��� : CPU�� �׻� 100%�̹Ƿ� �ٶ������� �ʴ�.
	for (;;) {
		if (PeekMessage(&Message,NULL,0,0,PM_REMOVE)) {
			if (Message.message==WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {
			OnIdle();
		}
	}
//*/

//* OnIdle�� �� �� �̻� ȣ������ �ʵ��� �Ѵ� - ȸ���� �پ������ CPU �������� �������� �ʴ´�.
	/*BOOL AllowIdle=TRUE;
	for (;;) {
		if (PeekMessage(&Message,NULL,0,0,PM_REMOVE)) {
			if (Message.message==WM_QUIT)
				break;
			AllowIdle=TRUE;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {
			if (AllowIdle) {
				OnIdle();
				AllowIdle=FALSE;
			}
		}
	}*/
//*/

	// ó���� �޽����� ���� �� WaitMessage �Լ��� ȣ���Ͽ� ����ϵ��� �Ѵ�.
	BOOL AllowIdle = TRUE; 
	for (;;) {  
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
			if (Message.message == WM_QUIT)
				break;
			AllowIdle = TRUE;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {
			if (AllowIdle) {
				OnIdle();
				AllowIdle = FALSE;
			}
			WaitMessage();
		}
	}
		return Message.wParam;
}

void OnIdle()
{
	HDC hdc;
	hdc=GetDC(hWndMain);
	int x,y,r;
	HBRUSH hBrush,hOldBrush;

	x=rand() % 640;
	y=rand() % 480;
	r=rand() % 10+10;
	hBrush=CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));
	hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
	Ellipse(hdc,x-r,y-r,x+r,y+r);
	DeleteObject(SelectObject(hdc,hOldBrush));

	ReleaseDC(hWndMain,hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage) {
	case WM_MOUSEMOVE:
		wsprintf(str,TEXT("���콺 ��ġ=(%d,%d)"),LOWORD(lParam),HIWORD(lParam));
		SetWindowText(hWnd,str);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
