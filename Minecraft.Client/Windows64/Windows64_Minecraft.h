#pragma once
#include <string>
#include <functional>
#include "../../Minecraft.Server/Access/ServerAccessor.h"

typedef unsigned long long PlayerUID;

class Windows64Minecraft {
public:
	static void StartDedicatedServer(std::function<void(std::wstring, int)> enableProfiler);

	static ServerAccessor* getServerAccessor(std::string name);
private:
	static std::unordered_map<std::string, ServerAccessor*> serverAccessors;
};