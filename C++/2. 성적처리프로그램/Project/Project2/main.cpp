#include "manager.h"




ostream& operator<<(ostream& cout, const String& ms)
{
    if (ms.length > 0) cout << ms.characters;
    return cout;
}
istream& operator>>(istream& cin, String& ms)
{
    char* tmp = new char[10000];
    cin >> tmp;
    ms = tmp;
    return cin;
}

 

int main()   
{
    Manager* manager = new Manager();
    manager->Init();
    manager->Run();

    delete manager;
}
