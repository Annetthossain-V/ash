#pragma once
#include <string>
#include <vector>

namespace format {

std::vector<std::string> formatted_line(std::string line);
void formatted_line_free(char** line);

char** vector_to_char_ptr(std::vector<std::string>& split);

}
