#pragma once
#include <string>
#include <vector>
#include <map>

namespace format {

extern std::map<std::string, std::string> alias;

std::vector<std::string> formatted_line(std::string line);
void formatted_line_free(char** line);

char** vector_to_char_ptr(std::vector<std::string>& split);

void setalias(std::vector<std::string>& line);

}
