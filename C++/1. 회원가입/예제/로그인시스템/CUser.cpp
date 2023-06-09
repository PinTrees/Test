#include "CUser.h"

CUser::CUser(const char* _id, const char* _pw)
{
	strcpy(mId, _id);
	strcpy(mPw, _pw);
	mLoginState = false;
}

CUser::~CUser()
{

}

const char* CUser::GetId()
{
	return mId;
}

const char* CUser::GetPw()
{
	return mPw;
}

bool CUser::GetLoginState()
{
	return mLoginState;
}


bool CUser::SetId(const char* _id)
{
	strcpy(mId, _id);
	return true;
}

bool CUser::SetPw(const char* _pw)
{
	strcpy(mPw, _pw);
	return true;
}

void CUser::SetLogin()
{
	mLoginState = true;
}

void CUser::SetLogout()
{
	mLoginState = false;
}