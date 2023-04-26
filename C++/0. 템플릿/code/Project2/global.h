#pragma once
#include <ostream>
#include "string.h"

#define ARRAY_LEN(X) (sizeof(X)/sizeof(X[0]))
#define SAFE_DELETE(a) if(a != nullptr) { delete a; }
// �����ʿ�
#define SAFE_ARRAY_DELETE(a) if(a != nullptr) { delete[] a; }


// C# ������ ������Ƽ �ۼ� ��ũ�� - vs ������ ����
#define PROPERTY(_get,_set) _declspec(property(get = _get, put = _set))
#define PROPERTY_S(_set) _declspec(property(put = _set))
#define PROPERTY_G(_get) _declspec(property(get = _get))
//PROPERTY(GetTmp, SetTmp) int tmp;
//int GetTmp() { return aa; }
//void SetTmp(int _aa) { aa = _aa; }





// ��Ʈ ���ڿ��� ��ȯ�Լ�
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


// ��ȯ �Լ�
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


// ��Ŭ�� ���� ���� ��ũ��
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

// �̱��� ���� ���� ��ũ��
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

