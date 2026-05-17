#pragma once
#include "../ServerAccessor.h"
#include "../../Minecraft.World/x64headers/extraX64.h"

class BlacklistAccessor : ServerAccessor {
public:
	BlacklistAccessor() : ServerAccessor("blacklist", "") {
		nlohmann::json& jsonData = this->storage->GetData();
		if (!jsonData.contains("xuids")) {
			jsonData.push_back(nlohmann::json::array())
		}

		if (!jsonData.contains("ips")) {
			jsonData.push_back(nlohmann::json::array())
		}
	}

	bool IsPlayerBlacklisted(PlayerUID xuid) {
		std::string xuidString = std::to_string(xuid);

		return this->storage->GetData()["xuids"].contains(xuidString);
	}

	bool RemoveBlacklistedPlayer(PlayerUID xuid) {
		nlohmann::json& object = this->storage->GetData()["xuids"];
		std::string xuidString = std::to_string(xuid);

		auto itor = object.find(xuidString);

		if (itor != object.end()) {
			object.erase(itor);
		}

		return (itor != object.end());
	}

	void AddBlacklistedPlayer(PlayerUID xuid) {
		this->storage->GetData()["xuids"].push_back(std::to_string(xuid));
	}


	
	bool isAddressBlacklisted(std::string& address) {
		return this->storage->GetData()["ips"].contains(address);
	}

	bool RemoveBlacklistedAddress(std::string& address) {
		nlohmann::json& object = this->storage->GetData()["ips"];

		auto itor = object.find(address);

		if (itor != object.end()) {
			object.erase(itor);
		}

		return (itor != object.end());
	}

	bool AddBlacklistedAddress(std::string& address) {
		this->storage->GetData()["ips"].push_back(address);
	}
};