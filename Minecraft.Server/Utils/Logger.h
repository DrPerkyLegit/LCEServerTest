#pragma once
#include <cstdio>

class Logger {
public:
	static void Info(const char* message);
	static void Warning(const char* message);
	static void Error(const char* message);

	static void Info(const wchar_t* message);
	static void Warning(const wchar_t* message);

	static void Error(const wchar_t* message);
};