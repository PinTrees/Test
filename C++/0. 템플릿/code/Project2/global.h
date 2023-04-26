#pragma once
#include <ostream>
#include "string.h"

#define ARRAY_LEN(X) (sizeof(X)/sizeof(X[0]))
#define SAFE_DELETE(a) if(a != nullptr) { delete a; }
// 수정필요
#define SAFE_ARRAY_DELETE(a) if(a != nullptr) { delete[] a; }


// C# 형태의 프로퍼티 작성 매크로 - vs 에서만 가능
#define PROPERTY(_get,_set) _declspec(property(get = _get, put = _set))
#define PROPERTY_S(_set) _declspec(property(put = _set))
#define PROPERTY_G(_get) _declspec(property(get = _get))
//PROPERTY(GetTmp, SetTmp) int tmp;
//int GetTmp() { return aa; }
//void SetTmp(int _aa) { aa = _aa; }





// 인트 문자열간 변환함수
static char* intToChar(int a)
{
	char buff[8];
	sprintf_s(buff, "%d", a);
	return buff;
}
static int ToInt(char* str)
{
	return atoi(str);
}
static int ToInt(String str)
{
	return atoi(str.characters);
}
static int ToInt(String* str)
{
	return atoi(str->characters);
}


// 변환 함수
static char* ToChars(String* str)
{
	return str->characters;
}
static char* ToChars(String str)
{
	return str.characters;
}
static String ToString(int val)
{
	char buff[8];
	sprintf_s(buff, "%d", val);

	return String(buff);
}


static void CinClear()
{
	if (cin.fail())
	{
		cin.clear();
		while (getchar() != '\n');
	}
}


enum class MAINMENU { Inupt = 1, Print, Search, Save, Exit };
enum class PRODUCT { Goods = 1, Clothes, Electronic, };


// 싱클톤 패턴 생성 매크로
#define DECLARE_SINGLETONE(CLASSNAME)                                       \
        private:                                                            \
               CLASSNAME(const CLASSNAME&){}                                \
               CLASSNAME& operator=(const CLASSNAME&){}                     \
               CLASSNAME();                                                 \
               ~CLASSNAME();                                                \
			   static CLASSNAME* mPthis;                                    \
        public:                                                             \
               static CLASSNAME* Create();									\
			   static CLASSNAME* GetInstance();								\
               static void Destroy();				

// 싱글톤 패턴 구현 매크로
#define IMPLEMENT_SINGLETON(CLASSNAME)                              \
               CLASSNAME* CLASSNAME::mPthis= NULL;					\
                                                                    \
               CLASSNAME* CLASSNAME::Create()						\
			   {													\
                       if(mPthis == NULL)							\
						{											\
                              mPthis=new CLASSNAME();				\
						}											\
                        return mPthis;								\
               }                                                    \
               CLASSNAME* CLASSNAME::GetInstance()					\
               {                                                    \
                    return mPthis;									\
               }													\
			   void CLASSNAME::Destroy()							\
               {													\
					if(mPthis) delete mPthis;						\
			   }		

