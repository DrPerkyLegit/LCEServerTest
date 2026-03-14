#pragma once
#include <cstdio>

class Logger {
public:
	static void Info(const char* message);
	static void Warning(const char* message);
	static void Error(const char* message);

	static void SetColorMode(bool value);
private:
	static bool b_showColor;
};