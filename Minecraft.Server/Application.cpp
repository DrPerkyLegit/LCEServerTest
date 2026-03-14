#include "stdafx.h"

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING); //todo: find out why this breaks \n in printf calls

	Windows64ServerLink::StartDedicatedServer();
	return 0;
}