#include <stdafx.h>
#include "Logger.h"

bool Logger::b_showColor = false;

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

void Logger::SetColorMode(bool value) {
	Logger::b_showColor = false;
}