#define MAIN
#include "manager.h"
#include "console.h"


int main()   
{
    MainManager* manager = new MainManager();
    manager->Init();
    manager->Run();

    manager->Dispose();
    delete manager;
}
