#pragma once
#include <string>

namespace io {

std::string envinfo(const std::string name);
void create_env(const std::string name, const std::string value);

}
