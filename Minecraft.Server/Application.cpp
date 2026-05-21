#include <Windows.h>
#include <memory>
#include "Utils/Logger.h"
#include "../Minecraft.Client/Windows64/Windows64_Minecraft.h"

void enableProfiler(std::wstring password, int port);

int main() {
	//make things resolve correctly, taken from source and moved
	{
		char szExeDir[MAX_PATH] = {};
		GetModuleFileNameA(nullptr, szExeDir, MAX_PATH);
		char* pSlash = strrchr(szExeDir, '\\');
		if (pSlash) { *(pSlash + 1) = '\0'; SetCurrentDirectoryA(szExeDir); }
	}

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING); //todo: find out why this breaks \n in printf calls

	Windows64Minecraft::StartDedicatedServer(enableProfiler);
	return 0;
}


void enableProfiler(std::wstring password, int port) {

}
