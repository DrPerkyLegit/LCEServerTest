#pragma once
#include "../ServerAccessor.h"
#include "../../Minecraft.World/x64headers/extraX64.h"

class WhitelistAccessor : ServerAccessor {
public:
	WhitelistAccessor() : ServerAccessor("whitelist", "") {
		nlohmann::json& jsonData = this->storage->GetData();
		if (!jsonData.contains("accepted_xuids")) {
			jsonData.push_back(nlohmann::json::array())
		}

		if (!jsonData.contains("last_known_names")) {
			jsonData.push_back(nlohmann::json::array())
		}

		if (!jsonData.contains("pending_names")) {
			jsonData.push_back(nlohmann::json::array())
		}
	}

	bool IsPlayerWhitelisted(PlayerUID xuid, std::string name) {
		std::string xuidString = std::to_string(xuid);
		bool isAllowed = this->storage->GetData()["accepted_xuids"].contains(xuidString);

		if (isAllowed) {
			this->storage->GetData()["last_known_names"][xuidString] = name;
		}

		return isAllowed;
	}

	bool RemoveWhitelistedPlayer(PlayerUID xuid, std::string name) {
		nlohmann::json& object = this->storage->GetData()["accepted_xuids"];
		nlohmann::json& knownObject = this->storage->GetData()["last_known_names"];

		std::string xuidString = std::to_string(xuid);

		auto itor = object.find(xuidString);

		if (itor != object.end()) {
			object.erase(itor);

			auto knownItor = knownObject.find(xuidString);
			if (knownItor != knownObject.end()) {
				knownObject.erase(itor);
			}
		}

		return (itor != object.end());
	}

	void AddWhitelistedPlayer(PlayerUID xuid, std::string name) {
		std::string xuidString = std::to_string(xuid);

		this->storage->GetData()["last_known_names"][xuidString] = name;
		this->storage->GetData()["accepted_xuids"].push_back(xuidString);
	}



	bool IsPlayerPendingWhitelisted(std::string name) {
		return this->storage->GetData()["pending_names"].contains(name);
	}

	bool RemoveWhitelistedPlayer(std::string name) {
		nlohmann::json& object = this->storage->GetData()["pending_names"];

		auto itor = object.find(name);
		if (itor != object.end()) {
			object.erase(itor);
		}

		return (itor != object.end());
	}

	void AddPendingPlayerWhitelist(const std::string& name) {
		this->storage->GetData()["pending_names"].push_back(name);
	}
};