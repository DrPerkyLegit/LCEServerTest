#include <stdafx.h>
#include "Logger.h"

void Logger::Info(const char* message) {
	printf("[INFO] %s\n", message);
	fflush(stdout);
}

void Logger::Warning(const char* message) {
	printf("[WARN] %s\n", message);
	fflush(stdout);
}

void Logger::Error(const char* message) {
	printf("[ERROR] %s\n", message);
	fflush(stdout);
}

void Logger::Info(const wchar_t* message) {
	wprintf(L"[INFO] %s\n", message);
	fflush(stdout);
}

void Logger::Warning(const wchar_t* message) {
	wprintf(L"[WARN] %s\n", message);
	fflush(stdout);
}

void Logger::Error(const wchar_t* message) {
	wprintf(L"[ERROR] %s\n", message);
	fflush(stdout);
}