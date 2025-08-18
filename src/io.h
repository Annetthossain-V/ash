#pragma once
#include <string>
#include <vector>

namespace io {

std::string envinfo(const std::string name);
void create_env(const std::string name, const std::string value);

void import_handler(std::vector<std::string>& line);
void export_handler(std::vector<std::string>& line);

}
