#pragma once
#include <string>
#include <functional>

typedef unsigned long long PlayerUID;

class Windows64Minecraft {
public:
	static void StartDedicatedServer(std::function<void()> pluginload);
};