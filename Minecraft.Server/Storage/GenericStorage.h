#pragma once

#include "../../include/nlohmann_json/json.hpp"

class GenericStorage {
public:
	GenericStorage(std::string name, std::string path);
	~GenericStorage();

	void SaveToDisk();
	bool inline LoadedFromFile() const { return this->loadedFromFile; }

	nlohmann::json& GetData() { return data; }
private:
	//do we really need to save the file and the path like this?
	std::string name;
	std::string path;

	std::string filePath;

	nlohmann::json data;

	bool loadedFromFile = false;
};