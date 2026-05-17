#pragma once
#include <string>
#include <memory>

#include "../Storage/GenericStorage.h"

class ServerAccessor {
public:
	ServerAccessor(std::string name, std::string path = "");
	virtual ~ServerAccessor() = default;

protected:
	std::shared_ptr<GenericStorage> storage;
};