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
		// ���� ������ ���� ������
		SQLCHAR InCon[255];
		SQLCHAR OutCon[1024];
		SQLSMALLINT cbOutCon;
		TCHAR Dir[MAX_PATH];
		SQLRETURN Ret;

		// ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
			return FALSE;
		if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
			SQL_IS_INTEGER) != SQL_SUCCESS)
			return FALSE;

		// ���� �ڵ��� �Ҵ��ϰ� �����Ѵ�.
		if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
			return FALSE;

		// MDB ���Ͽ� �����ϱ�
		GetCurrentDirectory(MAX_PATH, Dir);
		wsprintf((TCHAR*)InCon, "DRIVER={Microsoft Access Driver (*.mdb)};"
			"DBQ=%s\\logininfo.mdb;", Dir);
		Ret = SQLDriverConnect(hDbc, hwnd, InCon, sizeof(InCon), OutCon, sizeof(OutCon),
			&cbOutCon, SQL_DRIVER_NOPROMPT);

		if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
			return FALSE;

		// ��� �ڵ��� �Ҵ��Ѵ�.
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
			return FALSE;

		return TRUE;
	}
	void DBDisConnect()
	{
		// ������
		if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		if (hDbc) SQLDisconnect(hDbc);
		if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
		if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	}


	/// <summary>
	/// ���� ������ ��ȯ�ϴ� ���·� ����
	/// </summary>
	/// <param name="fptr"></param>
	/// <param name="query"></param>
	/// <returns></returns>
	bool DBExecuteSQL(std::function<void(UserData*)> fptr, char* query)
	{
		// ������� �����ޱ� ���� ������
		SQLTCHAR ID[21];
		SQLTCHAR PW[48];
		SQLTCHAR Name[48];
		SQLINTEGER lName, lPrice, lKorean;
		// ȭ�� ����� ���� ������
		int y = 1;
		int arTab[2] = { 200,400 };
		TCHAR str[255]; 


		// ����� �����ޱ� ���� ���ε��Ѵ�.
		SQLBindCol(hStmt, 1, SQL_C_CHAR, ID, sizeof(ID), &lName);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, PW, sizeof(PW), &lPrice);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, Name, sizeof(Name), &lKorean);

		// SQL���� �����Ѵ�.
		if (SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS) != SQL_SUCCESS) {
			fptr(nullptr);
			return FALSE;
		}

		// �о�� ������ ���
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