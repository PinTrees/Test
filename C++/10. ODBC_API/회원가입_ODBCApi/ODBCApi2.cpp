#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include "SQL.h"
#include "resource.h"
#include "list.h"
#include <functional>
#include "user.h"

///
/// logininfo.mdb
/// abcd,	 1234, 신규유저
/// testid2, 1234, 테스트유저
/// testid3, 1234, 테스트유저
/// testid4, 1234, 테스트유저


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("ODBCApi2");

BOOL CALLBACK MajorDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MajorDlgProc);

	return 0;
}

// 핸들
SQLHENV hEnv;
SQLHDBC hDbc;
SQLHSTMT hStmt;

SQLManager* sqlManager;
HWND fileditID;
HWND fileditPW;
bool isLogin = true;

BOOL CALLBACK MajorDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_INITDIALOG:
		sqlManager = new SQLManager(hDlg);
		sqlManager->DBConnect();

		fileditID = GetDlgItem(hDlg, IDC_EDIT1);
		fileditPW = GetDlgItem(hDlg, IDC_EDIT2);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			char buff1[1024];
			char buff2[1024];
			char query[1024];

			GetWindowText(fileditID, buff1, sizeof(buff1));
			GetWindowText(fileditPW, buff2, sizeof(buff2));
			sprintf(query, "select * from jointbl where ID='%s'", buff1);
			sqlManager->DBExecuteSQL([&](UserData* user) {
				if (user == nullptr) { isLogin = false; }
				else { isLogin = true; }
				}, query);

			if (isLogin) MessageBox(hWndMain, "로그인 성공", "알림", S_OK);
			else MessageBox(hWndMain, "로그인 실패", "알림", S_OK);

			return TRUE;
		}
		case IDC_BUTTON2: {
			char buff1[1024];
			char buff2[1024];
			char query[1024];

			GetWindowText(fileditID, buff1, sizeof(buff1));
			GetWindowText(fileditPW, buff2, sizeof(buff2));
			sprintf(query, "Insert into jointbl (ID,PW,UserName) VALUES ('%s','%s','유저이름')", buff1, buff2);
			bool result = sqlManager->SetQuery(query);

			if (result) MessageBox(hWndMain, "회원가입 성공", "알림", S_OK);
			else MessageBox(hWndMain, "회원가입 실패", "알림", S_OK);

			return TRUE;
		}
		case IDC_BUTTON3: {
			char buff1[1024];
			char buff2[1024];
			char query[1024]; 

			GetWindowText(fileditID, buff1, sizeof(buff1));
			GetWindowText(fileditPW, buff2, sizeof(buff2));
			sprintf(query, "Delete from jointbl where ID='%s' and PW='%s'", buff1, buff2);
			bool result = sqlManager->SetQuery(query);

			if (result) MessageBox(hWndMain, "회원탈퇴 성공", "알림", S_OK);
			else MessageBox(hWndMain, "회원탈퇴 실패", "알림", S_OK);

			return TRUE;
		}
		case IDCANCEL:
			sqlManager->DBDisConnect();
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
