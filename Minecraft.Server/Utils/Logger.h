#pragma once
#include <cstdio>

class Logger {
public:
	static void Info(const char* message) {
		printf("[INFO] %s\n", message);
		fflush(stdout);
	}
	static void Warning(const char* message) {
		printf("[INFO] %s\n", message);
		fflush(stdout);
	}
	static void Error(const char* message) {
		printf("[INFO] %s\n", message);
		fflush(stdout);
	}

	static void Info(const wchar_t* message) {
		wprintf(L"[INFO] %s\n", message);
		fflush(stdout);
	}
	static void Warning(const wchar_t* message) {
		wprintf(L"[INFO] %s\n", message);
		fflush(stdout);
	}

	static void Error(const wchar_t* message) {
		wprintf(L"[INFO] %s\n", message);
		fflush(stdout);
	}
};