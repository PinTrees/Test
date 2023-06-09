#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <functional>
#include "user.h"

class SQLManager
{
public:
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;
	HWND hwnd;

	SQLManager(HWND hwnd) { this->hwnd = hwnd; }

	bool DBConnect()
	{
		// 연결 설정을 위한 변수들
		SQLCHAR InCon[255];
		SQLCHAR OutCon[1024];
		SQLSMALLINT cbOutCon;
		TCHAR Dir[MAX_PATH];
		SQLRETURN Ret;

		// 환경 핸들을 할당하고 버전 속성을 설정한다.
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
			return FALSE;
		if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
			SQL_IS_INTEGER) != SQL_SUCCESS)
			return FALSE;

		// 연결 핸들을 할당하고 연결한다.
		if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
			return FALSE;

		// MDB 파일에 연결하기
		GetCurrentDirectory(MAX_PATH, Dir);
		wsprintf((TCHAR*)InCon, "DRIVER={Microsoft Access Driver (*.mdb)};"
			"DBQ=%s\\logininfo.mdb;", Dir);
		Ret = SQLDriverConnect(hDbc, hwnd, InCon, sizeof(InCon), OutCon, sizeof(OutCon),
			&cbOutCon, SQL_DRIVER_NOPROMPT);

		if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
			return FALSE;

		// 명령 핸들을 할당한다.
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
			return FALSE;

		return TRUE;
	}
	void DBDisConnect()
	{
		// 뒷정리
		if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		if (hDbc) SQLDisconnect(hDbc);
		if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
		if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	}


	/// <summary>
	/// 추후 맵으로 반환하는 형태로 구현
	/// </summary>
	/// <param name="fptr"></param>
	/// <param name="query"></param>
	/// <returns></returns>
	bool DBExecuteSQL(std::function<void(UserData*)> fptr, char* query)
	{
		// 결과값을 돌려받기 위한 변수들
		SQLTCHAR ID[21];
		SQLTCHAR PW[48];
		SQLTCHAR Name[48];
		SQLINTEGER lName, lPrice, lKorean;
		// 화면 출력을 위한 변수들
		int y = 1;
		int arTab[2] = { 200,400 };
		TCHAR str[255]; 


		// 결과를 돌려받기 위해 바인딩한다.
		SQLBindCol(hStmt, 1, SQL_C_CHAR, ID, sizeof(ID), &lName);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, PW, sizeof(PW), &lPrice);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, Name, sizeof(Name), &lKorean);

		// SQL문을 실행한다.
		if (SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS) != SQL_SUCCESS) {
			fptr(nullptr);
			return FALSE;
		}

		// 읽어온 데이터 출력
		//hdc = GetDC(hwnd);

		int index = 0;
		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			index++;
			TCHAR id[255];
			TCHAR pw[255];
			TCHAR name[255];
			wsprintf(id, "%s", ID);
			wsprintf(pw, "%s", PW);
			wsprintf(name, "%s", Name);
			//TabbedTextOut(hdc, 10, y * 20, str, lstrlen(str), 2, arTab, 0);
			y++;
			 
			fptr(new UserData(id, pw, name)); 
		
			SQLCloseCursor(hStmt); 
			return TRUE;
		};

		if (index == 0) {
			fptr(nullptr);
		}

		if (hStmt) SQLCloseCursor(hStmt);
		return TRUE;
	}

	bool SetQuery(char* query) {
		if (SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS) != SQL_SUCCESS) {
			return false;
		}
		else {
			return true;
		}
	}
};