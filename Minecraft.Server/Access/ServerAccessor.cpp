#include "ServerAccessor.h"

ServerAccessor::ServerAccessor(std::string name, std::string path) {
	this->storage = std::make_shared<GenericStorage>(name, path);
}
