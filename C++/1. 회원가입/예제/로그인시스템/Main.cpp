#include "CManager.h"

int main()
{
	CManager* manager = new CManager();
	manager->Run();
	delete manager;

	return 0;
}