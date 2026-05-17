#include "GenericStorage.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <Windows.h>

#include "../Utils/Logger.h"

using json = nlohmann::json;

GenericStorage::GenericStorage(std::string name, std::string path) {
    this->name = std::move(name);

    if (path.empty()) {
        char currentDir[MAX_PATH] = {};
        if (GetCurrentDirectoryA(MAX_PATH, currentDir) != 0) {
            this->path = std::move(currentDir);
        }
    } else {
        this->path = std::move(path);
    }

    std::filesystem::create_directories(this->path);

    this->filePath = this->path + "/" + this->name + ".jsonc";
    if (!std::filesystem::exists(this->filePath)) {
        std::ofstream createFile(this->filePath);

        json defaultJson = json::object();

        createFile << defaultJson.dump(4);
        createFile.close();
    }

    std::ifstream inputFile(this->filePath);

    if (inputFile.is_open()) {
        std::stringstream ss;
        ss << inputFile.rdbuf();

        std::string contents = ss.str();

        inputFile.close();

        this->data = json::parse(contents, nullptr, false, true); //dont parse comments - jsonc support
        if (this->data.is_discarded()) {
            this->data = json::object();
        } else {
            this->loadedFromFile = true;
        }
    } else {
        this->data = json::object();
    }
}

GenericStorage::~GenericStorage() {
    this->SaveToDisk();
}

void GenericStorage::SaveToDisk() {
    std::ofstream out(filePath);

    if (out.is_open()) {
        out << data.dump(4);
        out.close();
    } else {
        Logger::Error((std::string("Attempted to save config file (") + this->name + ") but it failed to save").c_str());
    }
}
